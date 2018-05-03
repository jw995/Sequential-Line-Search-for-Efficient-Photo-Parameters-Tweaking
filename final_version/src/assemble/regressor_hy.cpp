#include "regressor_hy.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/LU>
#include "utility.h"
#include "nloptutility.h"
#include <ctime>


using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;
using std::pair;

MatrixXd Regressor::calc_KK(const MatrixXd& X,
                            const double theta_d1, const double theta_d2,
                            const VectorXd& theta) {
    const unsigned N = X.cols();
    unsigned i, j;

    MatrixXd K(N, N);
    for (i = 0; i < N; ++i) {
        for (j = i; j < N; ++j) {
            auto value = Utility::ARD_squared_exponential_kernel(X.col(i), X.col(j), theta_d1, theta);
            K(i, j) = value;
            K(j, i) = value;
        }
    }

    return K + theta_d2*MatrixXd::Identity(N, N);
}

MatrixXd Regressor::KK_grad_d1(const MatrixXd& X,
                               const double theta_d1, const double /*theta_d2*/,
                               const VectorXd& theta) {
    const unsigned N = X.cols();
    unsigned i, j;

    MatrixXd grad_d1(N, N);
    for (i = 0; i < N; ++i) {
        for (j = i; j < N; ++j) {
            auto value = Utility::ARD_squared_exponential_kernel_derivative_a(X.col(i), X.col(j), theta_d1, theta);
            grad_d1(i, j) = value;
            grad_d1(j, i) = value;
        }
    }

    return grad_d1;
}

MatrixXd Regressor::KK_grad_d2(const MatrixXd& X,
                               const double /*theta_d1*/, const double /*theta_d2*/,
                               const VectorXd& /*theta*/) {
    const unsigned N = X.cols();
    return MatrixXd::Identity(N, N);
}

MatrixXd Regressor::KK_grad_theta_i(const MatrixXd& X,
	                                const double theta_d1, const double /*theta_d2*/,
                                    const VectorXd& theta, const unsigned idx) {
    const unsigned N = X.cols();
    unsigned i, j;

    MatrixXd grad_theta(N, N);
    for (i = 0; i < N; ++ i) {
        for (j = i; j < N; ++ j) {
            const VectorXd value =
                Utility::ARD_squared_exponential_kernel_derivative_r
                (X.col(i), X.col(j), theta_d1, theta);
            grad_theta(i, j) = value(idx);
            grad_theta(j, i) = value(idx);
        }
    }

    return grad_theta;
}


VectorXd Regressor::calc_k(const VectorXd& x, const MatrixXd& X,
	                       const double theta_d1, const double /*theta_d2*/,
                           const VectorXd& theta) {
    const unsigned N = X.cols();
    unsigned i;
    VectorXd k(N);

    for (i = 0; i < N; ++ i) {
        k(i) = Utility::ARD_squared_exponential_kernel
               (x, X.col(i), theta_d1, theta);
    }
    return k;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {

	// calculate gradiant
    inline double KK_grad_d1(const VectorXd& f, const MatrixXd& K_inv,
		                     const MatrixXd& X,
                             double theta_d1, double theta_d2,
                             const VectorXd& theta) {
        const double d1_prior = PreferenceRegressor::Params
                                ::getInstance().theta_d1;
        const double var = PreferenceRegressor::Params
                                ::getInstance().variance;

        const MatrixXd K_grad_d1 = Regressor::KK_grad_d1
                                   (X, theta_d1, theta_d2, theta);
        const double log_p_f_grad_d1 = 0.5 * f.transpose() *
									   K_inv * K_grad_d1 * K_inv *
                                       f - 0.5 * (K_inv * K_grad_d1).trace();
        const double log_prior = (std::log(d1_prior) - var - std::log(theta_d1))
                                 / (var * theta_d1);
        return log_p_f_grad_d1 + log_prior;
    }

    inline double KK_grad_d2(const VectorXd&f, const MatrixXd& K_inv,
		                     const MatrixXd& X,
                             double theta_d1, double theta_d2,
                             const VectorXd& theta) {
        const double d2_prior = PreferenceRegressor::Params
                                ::getInstance().theta_d2;
        const double      var = PreferenceRegressor::Params
                                ::getInstance().variance;

        const MatrixXd K_grad_d2 = Regressor::KK_grad_d2(X, theta_d1, theta_d2, theta);
        const double log_p_f_grad_d2 = 0.5 * f.transpose()
					  				   * K_inv * K_grad_d2 * K_inv * f
                                       - 0.5 * (K_inv * K_grad_d2).trace();
        const double log_prior = (std::log(d2_prior) - var - std::log(theta_d2))
                                 / (var * theta_d2);
        return log_p_f_grad_d2 + log_prior;
    }

    inline VectorXd KK_grad_theta(const VectorXd& f, const MatrixXd& K_inv,
		                          const MatrixXd& X,
                                  double theta_d1, double theta_d2,
                                  const VectorXd& theta) {
        unsigned i;
        const double theta_prior = PreferenceRegressor::Params
                                   ::getInstance().theta;
        const double         var = PreferenceRegressor::Params
                                   ::getInstance().variance;

        VectorXd grad = VectorXd::Zero(theta.rows());
        for (i = 0; i < theta.rows(); ++i) {
            const MatrixXd K_grad_theta = Regressor::KK_grad_theta_i(
                                          X, theta_d1, theta_d2, theta, i);
            const double log_p_f_grad_theta_i =
                0.5 * f.transpose() * K_inv * K_grad_theta * K_inv * f
                - 0.5 * (K_inv * K_grad_theta).trace();

            grad(i) += log_p_f_grad_theta_i;
        }

        for (i = 0; i < theta.rows(); ++i) {
            const double log_prior =
                (std::log(theta_prior) - var - std::log(theta(i)))
                / (var * theta(i));

            grad(i) += log_prior;
        }

        return grad;
    }

    // log p(d_k | f)
    inline double calc_log_likelihood(const Preference& p, const double w,
                                      const VectorXd& f) {
        unsigned i;
        const double btl_scale = w * PreferenceRegressor::Params
                                     ::getInstance().btl_scale;

        VectorXd tmp(p.size());
        for (i = 0; i < p.size(); ++ i) {
            tmp(i) = f(p[i]);
        }
        return std::log(Utility::BTL(tmp, btl_scale));
    }

    // Log likelihood that will be maximized
    double objective(const std::vector<double> &x, std::vector<double>& grad,
                     void* data) {
        unsigned i;
        const PreferenceRegressor* regressor =
            static_cast <PreferenceRegressor*> (data);

        const std::vector <Preference>& D = regressor->D;
        const MatrixXd& X = regressor->X;
        const VectorXd& w = regressor->w;
        const unsigned  M = X.cols();
        const VectorXd  f = Eigen::Map<const VectorXd>(&x[0], M);

        const double theta_d1 = (regressor->useMAPHyperparams) ?
			x[M + 0] : PreferenceRegressor::Params::getInstance().theta_d1;
        const double theta_d2 = (regressor->useMAPHyperparams) ?
			x[M + 1] : PreferenceRegressor::Params::getInstance().theta_d2;
        const VectorXd theta = (regressor->useMAPHyperparams) ?
            VectorXd(Eigen::Map<const VectorXd>(&x[M + 2], X.rows())) :
			VectorXd::Constant(X.rows(),
                               PreferenceRegressor::Params
                               ::getInstance().theta);

        double obj = 0.0;

        // Log likelihood of data
        for (i = 0; i < D.size(); ++ i) {
            obj += calc_log_likelihood(D[i], w(i), f);
        }

        // Log likelihood of f distribution
        const MatrixXd K     = Regressor::calc_KK(X, theta_d1, theta_d2, theta);
        const MatrixXd K_inv = K.inverse();
        const double   K_det = K.determinant();
        const double   term1 = - 0.5 * f.transpose() * K_inv * f;
        const double   term2 = - 0.5 * std::log(K_det);
        const double   term3 = - 0.5 * M * std::log(2.0 * M_PI);
        obj += term1 + term2 + term3;

        if (regressor->useMAPHyperparams) {
            // Priors for GP parameters
            const double d1_prior = PreferenceRegressor::Params::
                                    getInstance().theta_d1;
            const double d2_prior = PreferenceRegressor::Params::
                                    getInstance().theta_d2;
            const double theta_prior = PreferenceRegressor::Params::
                                       getInstance().theta;
            const double         var = PreferenceRegressor::Params::
                                       getInstance().variance;

            obj += std::log(Utility::log_normal(
                        theta_d1, std::log(d1_prior), var));
            obj += std::log(Utility::log_normal(
                        theta_d2, std::log(d2_prior), var));
            for (i = 0; i < theta.rows(); ++ i) {
                obj += std::log(Utility::log_normal(
                            theta(i), std::log(theta_prior), var));
            }
        }

        // When the algorithm is gradient-based, compute the gradient vector
        if (grad.size() == x.size()) {
            VectorXd grad_f = VectorXd::Zero(f.rows());

            // Accumulate per-data derivatives
            const double btl_scale = PreferenceRegressor::Params::
                                     getInstance().btl_scale;
            for (unsigned i = 0; i < D.size(); ++i) {
                const Preference& p = D[i];
                const double      s = btl_scale * w(i);
                VectorXd tmp1(p.size());

				for (unsigned i = 0; i < p.size(); ++i) {
					tmp1(i) = f(p[i]);
				}

                const VectorXd tmp2 = Utility::derivative_BTL(tmp1, s)
                                      / Utility::BTL(tmp1, s);
				for (unsigned i = 0; i < p.size(); ++i) {
					grad_f(p[i]) += tmp2(i);
				}
            }

            // Add GP term
            grad_f += - K_inv * f;

            Eigen::Map<VectorXd>(&grad[0], grad_f.rows()) = grad_f;

            if (regressor->useMAPHyperparams) {
                grad[M + 0] = KK_grad_d1(f, K_inv, X,
                                         theta_d1, theta_d2, theta);
                grad[M + 1] = KK_grad_d2(f, K_inv, X,
                                         theta_d1, theta_d2, theta);
                VectorXd grad_theta = KK_grad_theta(f, K_inv, X,
                                                    theta_d1, theta_d2, theta);

                for (unsigned i = 0; i < grad_theta.rows(); ++ i) {
                    grad[M + 2 + i] = grad_theta(i);
                }

            } else {
                grad[M + 0] = 0.0;
                grad[M + 1] = 0.0;
                grad[M + 2] = 0.0;
            }
        }

        return obj;
    }

}

PreferenceRegressor::PreferenceRegressor(const MatrixXd &X,
                                         const std::vector<Preference>& D,
                                         bool useMAPHyperparams) :
                                         useMAPHyperparams(useMAPHyperparams),
                                         X(X),
                                         D(D) {
    if (X.cols() == 0 || D.size() == 0) return;

    w = Eigen::VectorXd::Ones(D.size());

    compute_MAP();

    K     = calc_KK(X, theta_d1, theta_d2, theta);
    K_inv = K.inverse();
}

PreferenceRegressor::PreferenceRegressor(const MatrixXd &X,
                                         const std::vector<Preference>& D,
                                         const Eigen::VectorXd &w,
                                         bool useMAPHyperparams) :
                                         useMAPHyperparams(useMAPHyperparams),
                                         X(X),
                                         D(D),
                                         w(w) {
    if (X.cols() == 0 || D.size() == 0) return;

    compute_MAP();

    K     = calc_KK(X, theta_d1, theta_d2, theta);
    K_inv = K.inverse();
}

PreferenceRegressor::PreferenceRegressor(const MatrixXd &X,
                                         const std::vector<Preference>& D,
	                                     const Eigen::VectorXd &w,
                                         bool useMAPHyperparams,
                                         const PreferenceRegressor* prev) :
                                         useMAPHyperparams(useMAPHyperparams),
                                         X(X),
                                         D(D),
                                         w(w) {
    if (X.cols() == 0 || D.size() == 0) return;

    compute_MAP(prev);

	K = calc_KK(X, theta_d1, theta_d2, theta);
	K_inv = K.inverse();
}

double PreferenceRegressor::predict_miu(const VectorXd &x) const {
    const VectorXd k = Regressor::calc_k(x, X, theta_d1, theta_d2, theta);
    return k.transpose() * K_inv * f;
}

double PreferenceRegressor::predict_sigma_sq(const VectorXd &x) const {
    const VectorXd k = Regressor::calc_k(x, X, theta_d1, theta_d2, theta);
    return std::sqrt(theta_d1 + theta_d2 - k.transpose() * K_inv * k);
}

void PreferenceRegressor::compute_MAP(const PreferenceRegressor *prev) {
    const unsigned M = X.cols();
    const unsigned d = X.rows();

    VectorXd upper = VectorXd::Constant(M + 2 + d, + 1e+01);
    VectorXd lower = VectorXd::Constant(M + 2 + d, - 1e+01);
             lower.block(M, 0, 2 + d, 1) = VectorXd::Constant(2 + d, 1e-05);
    VectorXd x_ini = VectorXd::Constant(M + 2 + d, 0.0);
    x_ini(M + 0) = Params::getInstance().theta_d1;
    x_ini(M + 1) = Params::getInstance().theta_d2;
    x_ini.block(M + 2, 0, d, 1) = VectorXd::Constant(d, Params::getInstance().theta);

    // Use the MAP estimated values in prev regression as initial values
    if (prev != nullptr) {
        for (unsigned i = 0; i < M; ++ i) {
            x_ini(i) = prev->predict_miu(X.col(i));
        }

        x_ini(M + 0) = prev->theta_d1;
        x_ini(M + 1) = prev->theta_d2;
        x_ini.block(M + 2, 0, d, 1) = prev->theta;
    }

    const VectorXd x_opt = nloptUtility::compute(x_ini, upper, lower, objective,
                                                 this, nlopt::LD_TNEWTON, 500);
    f = x_opt.block(0, 0, M, 1);

    if (useMAPHyperparams) {
        theta_d1 = x_opt(M + 0);
        theta_d2 = x_opt(M + 1);
        theta = x_opt.block(M + 2, 0, d, 1);
    } else {
        theta_d1 = PreferenceRegressor::Params::getInstance().theta_d1;
        theta_d2 = PreferenceRegressor::Params::getInstance().theta_d2;
        theta = VectorXd::Constant(d, PreferenceRegressor::Params::
                                      getInstance().theta);
    }
}

VectorXd PreferenceRegressor::find_arg_max() {
    const unsigned M = X.rows();

    assert (M != 0);

    int i; f.maxCoeff(&i);
    return X.col(i);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {

    const bool   useLogNormalPrior      = true;
    const double d1_prior_mu            = std::log(0.500);
    const double d1_prior_sigma_squared = 0.10;
    const double d2_prior_mu            = std::log(0.001);
    const double d2_prior_sigma_squared = 0.10;
    const double theta_prior_mu            = std::log(0.500);
    const double theta_prior_sigma_squared = 0.10;

    double grad_d1_prior(const double theta_d1) {
        return (d1_prior_mu - d1_prior_sigma_squared - std::log(theta_d1))
               / (d1_prior_sigma_squared * theta_d1);
    }

    double grad_d2_prior(const double theta_d2) {
        return (d2_prior_mu - d2_prior_sigma_squared - std::log(theta_d2))
               / (d2_prior_sigma_squared * theta_d2);
    }

    double grad_theta_i_prior(const Eigen::VectorXd &theta, const int idx) {
        return (theta_prior_mu - theta_prior_sigma_squared
			    - std::log(theta(idx)))
                / (theta_prior_sigma_squared * theta(idx));
    }

    double theta_d1_prior(const double theta_d1) {
        return std::log(Utility::log_normal(theta_d1, d1_prior_mu,
                                            d1_prior_sigma_squared));
    }

    double theta_d2_prior(const double theta_d2) {
        return std::log(Utility::log_normal(theta_d2, d2_prior_mu,
                                            d2_prior_sigma_squared));
    }

    double theta_i_prior(const Eigen::VectorXd &theta, const int idx) {
        return std::log(Utility::log_normal(theta(idx), theta_prior_mu,
                                            theta_prior_sigma_squared));
    }

    double grad_d1(const MatrixXd& X, const MatrixXd& K_inv, const VectorXd& f,
                   const double theta_d1, const double theta_d2,
                   const VectorXd& theta) {
        const MatrixXd K_grad_d1 = Regressor::KK_grad_d1(
                                   X, theta_d1, theta_d2, theta);
        const double term1 = + 0.5 * f.transpose() * K_inv
                             * K_grad_d1 * K_inv * f;
        const double term2 = - 0.5 * (K_inv * K_grad_d1).trace();
        return term1 + term2
               + (useLogNormalPrior ? grad_d1_prior(theta_d1) : 0.0);
    }

    double grad_d2(const MatrixXd& X, const MatrixXd& K_inv, const VectorXd& f,
                   const double theta_d1, const double theta_d2,
                   const VectorXd& theta) {
        const MatrixXd K_grad_d2 = Regressor::KK_grad_d2(
                                   X, theta_d1, theta_d2, theta);
        const double term1 = + 0.5 * f.transpose() * K_inv
                             * K_grad_d2 * K_inv * f;
        const double term2 = - 0.5 * (K_inv * K_grad_d2).trace();
        return term1 + term2
               + (useLogNormalPrior ? grad_d2_prior(theta_d2) : 0.0);
    }

    double grad_theta_i(const MatrixXd& X, const MatrixXd& K_inv,
                        const VectorXd& f,
                        const double theta_d1, const double theta_d2,
                        const VectorXd& theta, const int idx) {
        const MatrixXd K_grad_theta_i = Regressor::KK_grad_theta_i(
                                        X, theta_d1, theta_d2, theta, idx);
        const double term1 = + 0.5 * f.transpose() * K_inv
                             * K_grad_theta_i * K_inv * f;
        const double term2 = - 0.5 * (K_inv * K_grad_theta_i).trace();
        return term1 + term2
               + (useLogNormalPrior ? grad_theta_i_prior(theta, idx) : 0.0);
    }

    VectorXd calc_grad(const MatrixXd& X, const MatrixXd& K_inv,
		               const VectorXd& f,
                       const double theta_d1, const double theta_d2,
                       const VectorXd& theta) {
        const unsigned D = X.rows();

        VectorXd grad(D + 2);
        grad(0) = grad_d1(X, K_inv, f, theta_d1, theta_d2, theta);
        grad(1) = grad_d2(X, K_inv, f, theta_d1, theta_d2, theta);

        for (unsigned i = 2; i < D + 2; ++ i) {
            const unsigned idx = i - 2;
            grad(i) = grad_theta_i(X, K_inv, f, theta_d1, theta_d2, theta, idx);
        }

        return grad;
    }

    struct Data
	{
        Data(const MatrixXd& X, const VectorXd& f) : X(X), f(f){}

        const MatrixXd X;
        const VectorXd f;
    };

    // Counting the number of function evaluations
    unsigned count;

    // Log likelihood that will be maximized
    double GaussObjective(const std::vector<double> &x, std::vector<double>& grad, void* data) {
        // Count the number of evaluations
        ++ count;

        const MatrixXd& X = static_cast<const Data*>(data)->X;
        const VectorXd& f = static_cast<const Data*>(data)->f;

        const unsigned N = X.cols();

        const double   theta_d1 = x[0];
        const double   theta_d2 = x[1];
        const VectorXd theta = [&x]() {
            std::vector<double> _x = x;
            return Eigen::Map<VectorXd>(&_x[2], _x.size() - 2);
        }();

        const MatrixXd K     = Regressor::calc_KK(X, theta_d1, theta_d2, theta);
        const MatrixXd K_inv = K.inverse();

        // When the algorithm is gradient-based, compute the gradient vector
        if (grad.size() == x.size()) {
            const VectorXd g = calc_grad(X, K_inv, f, theta_d1, theta_d2, theta);

			for (unsigned i = 0; i < g.rows(); ++i) {
				grad[i] = g(i);
			}
        }

        const double term1 = - 0.5 * f.transpose() * K_inv * f;
        const double term2 = - 0.5 * std::log(K.determinant());
        const double term3 = - 0.5 * N * std::log(2.0 * M_PI);

        // Computing the regularization terms from a prior assumptions
        const double d1_prior = theta_d1_prior(theta_d1);
        const double d2_prior = theta_d2_prior(theta_d2);
        const double theta_prior = [&theta]() {
            double sum = 0.0;
			for (unsigned i = 0; i < theta.rows(); ++i) {
				sum += theta_i_prior(theta, i);
			}

            return sum;
        }();

        const double regularization = useLogNormalPrior ?
                                      (d1_prior + d2_prior + theta_prior) : 0.0;

        return term1 + term2 + term3 + regularization;
    }

}


GaussianProcessRegressor::GaussianProcessRegressor(
        const MatrixXd& X, const VectorXd& f) {
    this->X = X;
    this->f = f;

    if (X.rows() == 0) return;

    compute_MAP();

    K     = calc_KK(X, theta_d1, theta_d2, theta);
    K_inv = K.inverse();
}

GaussianProcessRegressor::GaussianProcessRegressor(
        const Eigen::MatrixXd &X, const Eigen::VectorXd &f,
	    double theta_d1, double theta_d2, const Eigen::VectorXd &theta) {
    this->X = X;
    this->f = f;
    this->theta_d1 = theta_d1;
    this->theta_d2 = theta_d2;
    this->theta = theta;

    K     = calc_KK(X, theta_d1, theta_d2, theta);
    K_inv = K.inverse();
}

double GaussianProcessRegressor::predict_miu(const VectorXd &x) const {
    const VectorXd k = calc_k(x, X, theta_d1, theta_d2, theta);
    return k.transpose() * K_inv * f;
}

double GaussianProcessRegressor::predict_sigma_sq(const VectorXd &x) const {
    const VectorXd k = calc_k(x, X, theta_d1, theta_d2, theta);
    return std::sqrt(theta_d1 + theta_d2 - k.transpose() * K_inv * k);
}

void GaussianProcessRegressor::compute_MAP() {
    const unsigned D = X.rows();

    Data data(X, f); // Constant during optimization

    const VectorXd x_ini = VectorXd::Constant(D + 2, 1e+00);
    const VectorXd upper = VectorXd::Constant(D + 2, 5e+01);
    const VectorXd lower = VectorXd::Constant(D + 2, 1e-08);

    const VectorXd x_glo = nloptUtility::compute(x_ini, upper, lower, objective, &data, nlopt::GN_DIRECT, 300);

    const VectorXd x_loc = nloptUtility::compute(x_glo, upper, lower, objective, &data, nlopt::LD_TNEWTON, 1000);

    theta_d1 = x_loc(0);
    theta_d2 = x_loc(1);
    theta = x_loc.block(2, 0, D, 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ExpectedImprovement {

    double objective(const std::vector<double> &x,
                     std::vector<double>& /*grad*/, void* data) {
        const Regressor* regressor = static_cast<const Regressor*>(data);
        return calculateExpectedImprovedment(
                *regressor, Eigen::Map<const VectorXd>(&x[0], x.size()));
    }

    double calculateExpectedImprovedment(const Regressor &regressor,
                                         const VectorXd& x) {
        if (regressor.getf().rows() == 0) return 0.0;

        const double f_best = regressor.getf().maxCoeff();
        const double s_x    = regressor.predict_sigma_sq(x);
        const double u      = (regressor.predict_miu(x) - f_best) / s_x;
        const double Phi    = 0.5 * std::erf(u / std::sqrt(2.0)) + 0.5;
        const double phi    = (1.0/std::sqrt(2.0 * M_PI)) * std::exp(-u*u/2.0);
        const double EI     = (regressor.predict_miu(x)-f_best)*Phi + s_x*phi;

        return (s_x < 1e-10 || std::isnan(EI)) ? 0.0 : EI;
    }

    VectorXd findNextPoint(Regressor& regressor) {
        const unsigned D = regressor.getX().rows();

        const VectorXd upper = VectorXd::Constant(D, 1.0);
        const VectorXd lower = VectorXd::Constant(D, 0.0);
        const VectorXd x_ini = VectorXd::Constant(D, 0.5);

        const VectorXd x_star_global =
            nloptUtility::compute(x_ini, upper, lower, objective,
                                  &regressor, nlopt::GN_DIRECT, 800);
        const VectorXd x_star_local  =
            nloptUtility::compute(x_star_global, upper, lower, objective,
                                  &regressor, nlopt::LN_COBYLA, 200);

        return x_star_local;
    }

    double obj(const std::vector<double> &x, std::vector<double>& /*grad*/, void* data) {
        const Regressor* origRegressor =
            static_cast<pair<const Regressor*,
                             const GaussianProcessRegressor*>*>(data)->first;
        const GaussianProcessRegressor* updatedRegressor =
            static_cast<pair<const Regressor*,
                             const GaussianProcessRegressor*>*>(data)->second;

        const VectorXd _x = Eigen::Map<const VectorXd>(&x[0], x.size());

        const double f_best = origRegressor->getf().maxCoeff();
        const double s_x    = updatedRegressor->predict_sigma_sq(_x);
        const double u      = (origRegressor->predict_miu(_x) - f_best) / s_x;
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

        GaussianProcessRegressor reg(regressor.getX(), regressor.getf(),
			regressor.get_theta_d1(), regressor.get_theta_d2(), regressor.get_theta());

        for (unsigned i = 0; i < n; ++i) {
            pair <const Regressor*, const GaussianProcessRegressor*>
                data(&regressor, &reg);
            const VectorXd x_star_global =
                nloptUtility::compute(x_ini, upper, lower, obj,
                                      &data, nlopt::GN_DIRECT, 800);
            const VectorXd x_star_local =
                nloptUtility::compute(x_star_global, upper, lower, obj,
                                      &data, nlopt::LN_COBYLA, 200);

            points.push_back(x_star_local);

            if (i + 1 == n) {
                break;
            }

            const unsigned N = reg.getX().cols();

            MatrixXd newX(D, N + 1);
            newX.block(0, 0, D, N) = reg.getX();
            newX.col(N) = x_star_local;

            VectorXd newF(reg.getf().rows() + 1);
            newF << reg.getf(), reg.predict_miu(x_star_local);

            reg = GaussianProcessRegressor(newX, newF,
                    regressor.get_theta_d1(), regressor.get_theta_d2(),
                    regressor.get_theta());
        }

        return points;
    }

}
