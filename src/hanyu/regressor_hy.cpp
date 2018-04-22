#include "regressor_hy.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/LU>
#include "utility.h"
#include "nloptutility.h"
#include "timer.h"
#include <ctime>


using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;
using std::pair;

MatrixXd Regressor::calc_C(const MatrixXd& X, const double a, const double b, const VectorXd& r){
    const unsigned N = X.cols();

    MatrixXd C(N, N);
    for (unsigned i = 0; i < N; ++ i){
        for (unsigned j = i; j < N; ++ j){
            const double value = Utility::ARD_squared_exponential_kernel(X.col(i), X.col(j), a, r);
            C(i, j) = value;
            C(j, i) = value;
        }
    }

    return C + b * MatrixXd::Identity(N, N);
}

MatrixXd Regressor::calc_C_grad_a(const MatrixXd& X, const double a, const double /*b*/, const VectorXd& r){
    const unsigned N = X.cols();

    MatrixXd C_grad_a(N, N);
    for (unsigned i = 0; i < N; ++ i){
        for (unsigned j = i; j < N; ++ j){
            const double value = Utility::ARD_squared_exponential_kernel_derivative_a(X.col(i), X.col(j), a, r);
            C_grad_a(i, j) = value;
            C_grad_a(j, i) = value;
        }
    }

    return C_grad_a;
}

MatrixXd Regressor::calc_C_grad_b(const MatrixXd& X, const double /*a*/, const double /*b*/, const VectorXd& /*r*/){
    const unsigned N = X.cols();
    return MatrixXd::Identity(N, N);
}

MatrixXd Regressor::calc_C_grad_r_i(const MatrixXd& X, const double a, const double /*b*/, const VectorXd& r, const unsigned index){
    const unsigned N = X.cols();

    MatrixXd C_grad_r(N, N);
    for (unsigned i = 0; i < N; ++ i){
        for (unsigned j = i; j < N; ++ j){
            const VectorXd value = Utility::ARD_squared_exponential_kernel_derivative_r(X.col(i), X.col(j), a, r);
            C_grad_r(i, j) = value(index);
            C_grad_r(j, i) = value(index);
        }
    }

    return C_grad_r;
}

VectorXd Regressor::calc_k(const VectorXd& x, const MatrixXd& X, const double a, const double /*b*/, const VectorXd& r){
    const unsigned N = X.cols();

    VectorXd k(N);
    for (unsigned i = 0; i < N; ++ i){
        k(i) = Utility::ARD_squared_exponential_kernel(x, X.col(i), a, r);
    }

    return k;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {

    #ifdef NOISELESS
    const double b_fixed = 1e-06;
    #endif

    inline double calc_grad_a(const VectorXd& y, const MatrixXd& C_inv, const MatrixXd& X, double a, double b, const VectorXd& r){
        const double   a_prior  = PreferenceRegressor::Params::getInstance().a;
        const double   variance = PreferenceRegressor::Params::getInstance().variance;

        const MatrixXd C_grad_a             = Regressor::calc_C_grad_a(X, a, b, r);
        const double   log_p_f_theta_grad_a = 0.5 * y.transpose() * C_inv * C_grad_a * C_inv * y - 0.5 * (C_inv * C_grad_a).trace();
        const double   log_prior            = (std::log(a_prior) - variance - std::log(a)) / (variance * a);
        return log_p_f_theta_grad_a + log_prior;
    }

    #ifndef NOISELESS
    inline double calc_grad_b(const VectorXd& y, const MatrixXd& C_inv, const MatrixXd& X, double a, double b, const VectorXd& r){
        const double   b_prior  = PreferenceRegressor::Params::getInstance().b;
        const double   variance = PreferenceRegressor::Params::getInstance().variance;

        const MatrixXd C_grad_b             = Regressor::calc_C_grad_b(X, a, b, r);
        const double   log_p_f_theta_grad_b = 0.5 * y.transpose() * C_inv * C_grad_b * C_inv * y - 0.5 * (C_inv * C_grad_b).trace();
        const double   log_prior            = (std::log(b_prior) - variance - std::log(b)) / (variance * b);
        return log_p_f_theta_grad_b + log_prior;
    }
    #endif

    inline VectorXd calc_grad_r(const VectorXd& y, const MatrixXd& C_inv, const MatrixXd& X, double a, double b, const VectorXd& r){
        const double   r_prior  = PreferenceRegressor::Params::getInstance().r;
        const double   variance = PreferenceRegressor::Params::getInstance().variance;

        VectorXd grad = VectorXd::Zero(r.rows());
        for (unsigned i = 0; i < r.rows(); ++ i){
            const MatrixXd C_grad_r               = Regressor::calc_C_grad_r_i(X, a, b, r, i);
            const double   log_p_f_theta_grad_r_i = 0.5 * y.transpose() * C_inv * C_grad_r * C_inv * y - 0.5 * (C_inv * C_grad_r).trace();
            grad(i) += log_p_f_theta_grad_r_i;
        }
        for (unsigned i = 0; i < r.rows(); ++ i){
            const double log_prior = (std::log(r_prior) - variance - std::log(r(i))) / (variance * r(i));
            grad(i) += log_prior;
        }

        return grad;
    }

    // log p(d_k | f)
    inline double calc_log_likelihood(const Preference& p, const double w, const VectorXd& y){
        const double btl_scale = w * PreferenceRegressor::Params::getInstance().btl_scale;

        VectorXd tmp(p.size()); for (unsigned i = 0; i < p.size(); ++ i) tmp(i) = y(p[i]);
        return std::log(Utility::BTL(tmp, btl_scale));
    }

    // Log likelihood that will be maximized
    double objective(const std::vector<double> &x, std::vector<double>& grad, void* data){
        const PreferenceRegressor* regressor = static_cast<PreferenceRegressor*>(data);

        const MatrixXd&                X = regressor->X;
        const std::vector<Preference>& D = regressor->D;
        const VectorXd&                w = regressor->w;
        const unsigned                 M = X.cols();
        const VectorXd                 y = Eigen::Map<const VectorXd>(&x[0], M);

        const double   a = (regressor->use_MAP_hyperparameters) ? x[M + 0] : PreferenceRegressor::Params::getInstance().a;
    #ifdef NOISELESS
        const double   b = b_fixed;
    #else
        const double   b = (regressor->use_MAP_hyperparameters) ? x[M + 1] : PreferenceRegressor::Params::getInstance().b;
    #endif
        const VectorXd r = (regressor->use_MAP_hyperparameters) ? VectorXd(Eigen::Map<const VectorXd>(&x[M + 2], X.rows())) : VectorXd::Constant(X.rows(), PreferenceRegressor::Params::getInstance().r);

        double obj = 0.0;

        // Log likelihood of data
        for (unsigned i = 0; i < D.size(); ++ i){
            obj += calc_log_likelihood(D[i], w(i), y);
        }

        // Log likelihood of y distribution
        const MatrixXd C     = Regressor::calc_C(X, a, b, r);
        const MatrixXd C_inv = C.inverse();
        const double   C_det = C.determinant();
        const double   term1 = - 0.5 * y.transpose() * C_inv * y;
        const double   term2 = - 0.5 * std::log(C_det);
        const double   term3 = - 0.5 * M * std::log(2.0 * M_PI);
        obj += term1 + term2 + term3;

        if (regressor->use_MAP_hyperparameters){
            // Priors for GP parameters
            const double   a_prior  = PreferenceRegressor::Params::getInstance().a;
    #ifndef NOISELESS
            const double   b_prior  = PreferenceRegressor::Params::getInstance().b;
    #endif
            const double   r_prior  = PreferenceRegressor::Params::getInstance().r;
            const double   variance = PreferenceRegressor::Params::getInstance().variance;

            obj += std::log(Utility::log_normal(a, std::log(a_prior), variance));
    #ifndef NOISELESS
            obj += std::log(Utility::log_normal(b, std::log(b_prior), variance));
    #endif
            for (unsigned i = 0; i < r.rows(); ++ i){
                obj += std::log(Utility::log_normal(r(i), std::log(r_prior), variance));
            }
        }

        // When the algorithm is gradient-based, compute the gradient vector
        if (grad.size() == x.size()){
            VectorXd grad_y = VectorXd::Zero(y.rows());

            // Accumulate per-data derivatives
            const double btl_scale = PreferenceRegressor::Params::getInstance().btl_scale;
            for (unsigned i = 0; i < D.size(); ++ i){
                const Preference& p = D[i];
                const double      s = btl_scale * w(i);
                VectorXd tmp1(p.size()); for (unsigned i = 0; i < p.size(); ++ i) tmp1(i) = y(p[i]);
                const VectorXd tmp2 = Utility::derivative_BTL(tmp1, s) / Utility::BTL(tmp1, s);
                for (unsigned i = 0; i < p.size(); ++ i) grad_y(p[i]) += tmp2(i);
            }

            // Add GP term
            grad_y += - C_inv * y;

            Eigen::Map<VectorXd>(&grad[0], grad_y.rows()) = grad_y;

            if (regressor->use_MAP_hyperparameters){
                grad[M + 0] = calc_grad_a(y, C_inv, X, a, b, r);
    #ifdef NOISELESS
                grad[M + 1] = 0.0;
    #else
                grad[M + 1] = calc_grad_b(y, C_inv, X, a, b, r);
    #endif
                VectorXd grad_r = calc_grad_r(y, C_inv, X, a, b, r);
                for (unsigned i = 0; i < grad_r.rows(); ++ i){
                    grad[M + 2 + i] = grad_r(i);
                }
            }
            else{
                grad[M + 0] = 0.0;
                grad[M + 1] = 0.0;
                grad[M + 2] = 0.0;
            }
        }

        return obj;
    }

}

PreferenceRegressor::PreferenceRegressor(const MatrixXd &X, const std::vector<Preference>& D, bool use_MAP_hyperparameters) :
    use_MAP_hyperparameters(use_MAP_hyperparameters),
    X(X),
    D(D){
    if (X.cols() == 0 || D.size() == 0) return;

    w = Eigen::VectorXd::Ones(D.size());

    compute_MAP();

    C     = calc_C(X, a, b, r);
    C_inv = C.inverse();
}

PreferenceRegressor::PreferenceRegressor(const MatrixXd &X, const std::vector<Preference>& D, const Eigen::VectorXd &w, bool use_MAP_hyperparameters) :
    use_MAP_hyperparameters(use_MAP_hyperparameters),
    X(X),
    D(D),
    w(w){
    if (X.cols() == 0 || D.size() == 0) return;

    compute_MAP();

    C     = calc_C(X, a, b, r);
    C_inv = C.inverse();
}

PreferenceRegressor::PreferenceRegressor(const MatrixXd &X, const std::vector<Preference>& D, const Eigen::VectorXd &w, bool use_MAP_hyperparameters, const PreferenceRegressor* prev) :
    use_MAP_hyperparameters(use_MAP_hyperparameters),
    X(X),
    D(D),
    w(w){
    if (X.cols() == 0 || D.size() == 0) return;

    compute_MAP(prev);

    C     = calc_C(X, a, b, r);
    C_inv = C.inverse();
}

double PreferenceRegressor::predict_y(const VectorXd &x) const{
    const VectorXd k = Regressor::calc_k(x, X, a, b, r);
    return k.transpose() * C_inv * y;
}

double PreferenceRegressor::predict_sigma(const VectorXd &x) const {
    const VectorXd k = Regressor::calc_k(x, X, a, b, r);
    return std::sqrt(a + b - k.transpose() * C_inv * k);
}

void PreferenceRegressor::compute_MAP(const PreferenceRegressor *prev) {
    const unsigned M = X.cols();
    const unsigned d = X.rows();

    VectorXd upper = VectorXd::Constant(M + 2 + d, + 1e+01);
    VectorXd lower = VectorXd::Constant(M + 2 + d, - 1e+01); lower.block(M, 0, 2 + d, 1) = VectorXd::Constant(2 + d, 1e-05);
    VectorXd x_ini = VectorXd::Constant(M + 2 + d, 0.0);
    x_ini(M + 0) = Params::getInstance().a;
    x_ini(M + 1) = Params::getInstance().b;
    x_ini.block(M + 2, 0, d, 1) = VectorXd::Constant(d, Params::getInstance().r);

    // Use the MAP estimated values in prev regression as initial values
    if (prev != nullptr) {
        for (unsigned i = 0; i < M; ++ i) {
            x_ini(i) = prev->predict_y(X.col(i));
        }
        x_ini(M + 0) = prev->a;
        x_ini(M + 1) = prev->b;
        x_ini.block(M + 2, 0, d, 1) = prev->r;
    }

#ifdef VERBOSE
    Timer t("PreferenceRegressor::compute_MAP");
#endif

    const VectorXd x_opt = nloptUtility::compute(x_ini, upper, lower, objective, this, nlopt::LD_TNEWTON, 500);

    y = x_opt.block(0, 0, M, 1);

    if (use_MAP_hyperparameters) {
        a = x_opt(M + 0);
#ifdef NOISELESS
        b = b_fixed;
#else
        b = x_opt(M + 1);
#endif
        r = x_opt.block(M + 2, 0, d, 1);

#ifdef VERBOSE
        std::cout << "Learned hyperparameters ... a: " << a << ", \tb: " << b << ", \tr: " << r.transpose() << std::endl;
#endif
    }
    else {
        a = PreferenceRegressor::Params::getInstance().a;
        b = PreferenceRegressor::Params::getInstance().b;
        r = VectorXd::Constant(d, PreferenceRegressor::Params::getInstance().r);
    }
}

VectorXd PreferenceRegressor::find_arg_max() {
    const unsigned M = X.rows();

    assert (M != 0);

    int i; y.maxCoeff(&i);
    return X.col(i);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {

    const bool   useLogNormalPrior     = true;
    const double a_prior_mu            = std::log(0.500);
    const double a_prior_sigma_squared = 0.10;
    #ifdef NOISELESS
    const double b_fixed               = 1e-06;
    #else
    const double b_prior_mu            = std::log(0.001);
    const double b_prior_sigma_squared = 0.10;
    #endif
    const double r_prior_mu            = std::log(0.500);
    const double r_prior_sigma_squared = 0.10;

    double calc_grad_a_prior(const double a){
        return (a_prior_mu - a_prior_sigma_squared - std::log(a)) / (a_prior_sigma_squared * a);
    }

    #ifndef NOISELESS
    double calc_grad_b_prior(const double b){
        return (b_prior_mu - b_prior_sigma_squared - std::log(b)) / (b_prior_sigma_squared * b);
    }
    #endif

    double calc_grad_r_i_prior(const Eigen::VectorXd &r, const int index){
        return (r_prior_mu - r_prior_sigma_squared - std::log(r(index))) / (r_prior_sigma_squared * r(index));
    }

    double calc_a_prior(const double a){
        return std::log(Utility::log_normal(a, a_prior_mu, a_prior_sigma_squared));
    }

    #ifndef NOISELESS
    double calc_b_prior(const double b){
        return std::log(Utility::log_normal(b, b_prior_mu, b_prior_sigma_squared));
    }
    #endif

    double calc_r_i_prior(const Eigen::VectorXd &r, const int index){
        return std::log(Utility::log_normal(r(index), r_prior_mu, r_prior_sigma_squared));
    }

    double calc_grad_a(const MatrixXd& X, const MatrixXd& C_inv, const VectorXd& y, const double a, const double b, const VectorXd& r){
        const MatrixXd C_grad_a = Regressor::calc_C_grad_a(X, a, b, r);
        const double term1 = + 0.5 * y.transpose() * C_inv * C_grad_a * C_inv * y;
        const double term2 = - 0.5 * (C_inv * C_grad_a).trace();
        return term1 + term2 + (useLogNormalPrior ? calc_grad_a_prior(a) : 0.0);
    }

    #ifndef NOISELESS
    double calc_grad_b(const MatrixXd& X, const MatrixXd& C_inv, const VectorXd& y, const double a, const double b, const VectorXd& r){
        const MatrixXd C_grad_b = Regressor::calc_C_grad_b(X, a, b, r);
        const double term1 = + 0.5 * y.transpose() * C_inv * C_grad_b * C_inv * y;
        const double term2 = - 0.5 * (C_inv * C_grad_b).trace();
        return term1 + term2 + (useLogNormalPrior ? calc_grad_b_prior(b) : 0.0);
    }
    #endif

    double calc_grad_r_i(const MatrixXd& X, const MatrixXd& C_inv, const VectorXd& y, const double a, const double b, const VectorXd& r, const int index){
        const MatrixXd C_grad_r_i = Regressor::calc_C_grad_r_i(X, a, b, r, index);
        const double term1 = + 0.5 * y.transpose() * C_inv * C_grad_r_i * C_inv * y;
        const double term2 = - 0.5 * (C_inv * C_grad_r_i).trace();
        return term1 + term2 + (useLogNormalPrior ? calc_grad_r_i_prior(r, index) : 0.0);
    }

    VectorXd calc_grad(const MatrixXd& X, const MatrixXd& C_inv, const VectorXd& y, const double a, const double b, const VectorXd& r){
        const unsigned D = X.rows();

        VectorXd grad(D + 2);
        grad(0) = calc_grad_a(X, C_inv, y, a, b, r);
    #ifdef NOISELESS
        grad(1) = 0.0;
    #else
        grad(1) = calc_grad_b(X, C_inv, y, a, b, r);
    #endif

        for (unsigned i = 2; i < D + 2; ++ i){
            const unsigned index = i - 2;
            grad(i) = calc_grad_r_i(X, C_inv, y, a, b, r, index);
        }

        return grad;
    }

    struct Data{
        Data(const MatrixXd& X, const VectorXd& y) : X(X), y(y){}

        const MatrixXd X;
        const VectorXd y;
    };

    // For counting the number of function evaluations
    unsigned count;

    // Log likelihood that will be maximized
    double GaussObjective(const std::vector<double> &x, std::vector<double>& grad, void* data){
        // For counting the number of function evaluations
        ++ count;

        const MatrixXd& X = static_cast<const Data*>(data)->X;
        const VectorXd& y = static_cast<const Data*>(data)->y;

        const unsigned N = X.cols();

        const double   a = x[0];
    #ifdef NOISELESS
        const double   b = b_fixed;
    #else
        const double   b = x[1];
    #endif
        const VectorXd r = [&x]() { std::vector<double> _x = x; return Eigen::Map<VectorXd>(&_x[2], _x.size() - 2); }();

        const MatrixXd C     = Regressor::calc_C(X, a, b, r);
        const MatrixXd C_inv = C.inverse();

        // When the algorithm is gradient-based, compute the gradient vector
        if (grad.size() == x.size()){
            const VectorXd g = calc_grad(X, C_inv, y, a, b, r);
            for (unsigned i = 0; i < g.rows(); ++ i) grad[i] = g(i);
        }

        const double term1 = - 0.5 * y.transpose() * C_inv * y;
        const double term2 = - 0.5 * std::log(C.determinant());
        const double term3 = - 0.5 * N * std::log(2.0 * M_PI);

        // Computing the regularization terms from a prior assumptions
        const double a_prior = calc_a_prior(a);
    #ifdef NOISELESS
        const double b_prior = 1.0;
    #else
        const double b_prior = calc_b_prior(b);
    #endif
        const double r_prior = [&r](){
            double sum = 0.0;
            for (unsigned i = 0; i < r.rows(); ++ i) sum += calc_r_i_prior(r, i);
            return sum;
        }();
        const double regularization = useLogNormalPrior ? (a_prior + b_prior + r_prior) : 0.0;

        return term1 + term2 + term3 + regularization;
    }

}

GaussianProcessRegressor::GaussianProcessRegressor(const MatrixXd& X, const VectorXd& y){
    this->X = X;
    this->y = y;

    if (X.rows() == 0) return;

    compute_MAP();

    C     = calc_C(X, a, b, r);
    C_inv = C.inverse();
}

GaussianProcessRegressor::GaussianProcessRegressor(const Eigen::MatrixXd &X, const Eigen::VectorXd &y, double a, double b, const Eigen::VectorXd &r){
    this->X = X;
    this->y = y;
    this->a = a;
    this->b = b;
    this->r = r;

    C     = calc_C(X, a, b, r);
    C_inv = C.inverse();
}

double GaussianProcessRegressor::predict_y(const VectorXd &x) const{
    const VectorXd k = calc_k(x, X, a, b, r);
    return k.transpose() * C_inv * y;
}

double GaussianProcessRegressor::predict_sigma(const VectorXd &x) const{
    const VectorXd k = calc_k(x, X, a, b, r);
    return std::sqrt(a + b - k.transpose() * C_inv * k);
}

void GaussianProcessRegressor::compute_MAP(){
    const unsigned D = X.rows();

    Data data(X, y); // Constant during optimization

#ifdef VERBOSE
    const auto t1 = std::chrono::system_clock::now();
    count = 0;
#endif

    const VectorXd x_ini = VectorXd::Constant(D + 2, 1e+00);
    const VectorXd upper = VectorXd::Constant(D + 2, 5e+01);
    const VectorXd lower = VectorXd::Constant(D + 2, 1e-08);

    const VectorXd x_glo = nloptUtility::compute(x_ini, upper, lower, objective, &data, nlopt::GN_DIRECT, 300);

#ifdef VERBOSE
    const auto t2 = std::chrono::system_clock::now();
    const unsigned g_count = count;
    count = 0;
#endif

    const VectorXd x_loc = nloptUtility::compute(x_glo, upper, lower, objective, &data, nlopt::LD_TNEWTON, 1000);

    a = x_loc(0);
    b = x_loc(1);
    r = x_loc.block(2, 0, D, 1);

#ifdef NOISELESS
    b = b_fixed;
#endif

#ifdef VERBOSE
    const auto t3 = std::chrono::system_clock::now();
    const unsigned l_count = count;

    std::cout << "global optimization: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms, " << g_count << " evaluations, obj = " << GaussObjective(x_star_global, x_ini, &data) << std::endl;
    std::cout << "local optimization: " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << " ms, " << l_count << " evaluations, obj = " << GaussObjective(x_star_local, x_ini, &data) << std::endl;
    std::cout << "a = " << a << ", b = " << b << ", r = " << r.transpose() << std::endl;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ExpectedImprovement{

    double objective(const std::vector<double> &x, std::vector<double>& /*grad*/, void* data) {
        const Regressor* regressor = static_cast<const Regressor*>(data);
        return calculateExpectedImprovedment(*regressor, Eigen::Map<const VectorXd>(&x[0], x.size()));
    }

    double calculateExpectedImprovedment(const Regressor &regressor, const VectorXd& x) {
        if (regressor.gety().rows() == 0) return 0.0;

        const double y_best = regressor.gety().maxCoeff();
        const double s_x    = regressor.predict_sigma(x);
        const double u      = (regressor.predict_y(x) - y_best) / s_x;
        const double Phi    = 0.5 * std::erf(u / std::sqrt(2.0)) + 0.5;
        const double phi    = (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(- u * u / 2.0);
        const double EI     = (regressor.predict_y(x) - y_best) * Phi + s_x * phi;

        return (s_x < 1e-10 || std::isnan(EI)) ? 0.0 : EI;
    }

    VectorXd findNextPoint(Regressor& regressor){
        const unsigned D = regressor.getX().rows();

        const VectorXd upper = VectorXd::Constant(D, 1.0);
        const VectorXd lower = VectorXd::Constant(D, 0.0);
        const VectorXd x_ini = VectorXd::Constant(D, 0.5);

        const VectorXd x_star_global = nloptUtility::compute(x_ini, upper, lower, objective, &regressor, nlopt::GN_DIRECT, 800);
        const VectorXd x_star_local  = nloptUtility::compute(x_star_global, upper, lower, objective, &regressor, nlopt::LN_COBYLA, 200);

        return x_star_local;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Schonlau et al, Global Versus Local Search in Constrained Optimization of Computer Models, 1997.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    double obj(const std::vector<double> &x, std::vector<double>& /*grad*/, void* data) {
        const Regressor*                origRegressor    = static_cast<pair<const Regressor*, const GaussianProcessRegressor*>*>(data)->first;
        const GaussianProcessRegressor* updatedRegressor = static_cast<pair<const Regressor*, const GaussianProcessRegressor*>*>(data)->second;

        const VectorXd _x = Eigen::Map<const VectorXd>(&x[0], x.size());

        const double y_best = origRegressor->gety().maxCoeff();
        const double s_x    = updatedRegressor->predict_sigma(_x);
        const double u      = (origRegressor->predict_y(_x) - y_best) / s_x;
        const double Phi    = 0.5 * std::erf(u / std::sqrt(2.0)) + 0.5;
        const double phi    = (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(- u * u / 2.0);
        const double EI     = s_x * (u * Phi + phi);

        return (s_x < 1e-08 || std::isnan(EI)) ? 0.0 : EI;
    }

    vector<VectorXd> findNextPoints(const Regressor &regressor, unsigned n) {
        const unsigned D = regressor.getX().rows();

        const VectorXd upper = VectorXd::Constant(D, 1.0);
        const VectorXd lower = VectorXd::Constant(D, 0.0);
        const VectorXd x_ini = VectorXd::Constant(D, 0.5);

        vector<VectorXd> points;

        GaussianProcessRegressor reg(regressor.getX(), regressor.gety(), regressor.geta(), regressor.getb(), regressor.getr());

        for (unsigned i = 0; i < n; ++ i){
            pair<const Regressor*, const GaussianProcessRegressor*> data(&regressor, &reg);
            const VectorXd x_star_global = nloptUtility::compute(x_ini, upper, lower, obj, &data, nlopt::GN_DIRECT, 800);
            const VectorXd x_star_local  = nloptUtility::compute(x_star_global, upper, lower, obj, &data, nlopt::LN_COBYLA, 200);

            points.push_back(x_star_local);

            if (i + 1 == n) break;

            const unsigned N = reg.getX().cols();

            MatrixXd newX(D, N + 1);
            newX.block(0, 0, D, N) = reg.getX();
            newX.col(N) = x_star_local;

            VectorXd newY(reg.gety().rows() + 1);
            newY << reg.gety(), reg.predict_y(x_star_local);

            reg = GaussianProcessRegressor(newX, newY, regressor.geta(), regressor.getb(), regressor.getr());
        }

        return points;
    }

}