#include <cmath>
#include <random>
#include <Eigen/Core>
#include "mathutility.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;


namespace
{
    // "uniformDist(randSeed)" to generate a uniformly distributed random value
    // "normalDist(randSeed)" to generate a normally distributed random value
    std::random_device seed;
    std::default_random_engine randSeed(seed());
    std::uniform_real_distribution <double> uniformDist(0.0, 1.0);
    std::normal_distribution <double> normalDist(0.0, 1.0);
}

namespace MathUtility
{
    VectorXd calc_k(const VectorXd& x, const MatrixXd& X, const VectorXd& theta) {
        // X is the matrix that contains x'
        // each column of X is a x'

        const unsigned num = X.cols();

        VectorXd k(num);
        for (unsigned i = 0; i < num; ++i) {
            k(i) = ARD_kernel(x, X.col(i), theta);
        }
        return k;
    }

    MatrixXd calc_K(const MatrixXd& X, const VectorXd& theta) {
        const unsigned num = X.cols();
        const unsigned vec_num = theta.rows();

        auto theta_d2 = theta(vec_num - 1);

        MatrixXd K(num, num);
        for (unsigned i = 0; i < num; ++i) {
            for (unsigned j = i; j < num; ++j) {
                const double value = ARD_kernel(X.col(i), X.col(j), theta);
                K(i, j) = value;
                K(j, i) = value;
            }
        }

        return K + theta_d2 * MatrixXd::Identity(num, num);
        // adding the element theta_d2*kronecker_delta in ARD_kerel here as an identity matrix
    }

    VectorXd generateRandomVector(unsigned n) {
        VectorXd x(n);
        for (unsigned i = 0; i < n; ++ i) {
            x(i) = uniformDist(randSeed);
        }
        return x;
    }

    // Log-Normal Distribution
    // LN(x, mu, sigma^2)
    inline double logNormal(double x, double mu, double sigmasquare) {
        const double logx_mu = std::log(x)-mu;
        return 1.0 / x*std::sqrt(2.0*M_PI*sigmasquare)
               * std::exp(-logx_mu*logx_mu/(2.0*sigmasquare));
    }

    // Normal distribution
    // N(x; mu, sigma^2)
    inline double normal(double x, double mu, double sigmasquare) {
        const double x_mu = x-mu;
        const double twosigmasquare = 2.0*sigmasquare;
        return (1.0 / std::sqrt(M_PI * twosigmasquare))
               * std::exp(- (x_mu * x_mu) / twosigmasquare);
    }

    // Bradley-Terry-Luce Model
    //   f is a 1x3 vector in our case
    inline double BTL(VectorXd f, double scale = 1.0) {
        unsigned i;
        const unsigned dimension = f.rows();
        double sum = 0.0;
        for (i = 0; i < dimension; i++) {
            sum += std::exp(f(i) / scale);
        }
        return std::exp(f(0) / scale) / sum;
    }

    inline VectorXd dBTL(const VectorXd& f, double scale = 1.0) {
        unsigned i;
        const unsigned dimension = f.rows();
        const double btl = BTL(f, scale);
        const double tmp = -btl*btl / scale;

        VectorXd d(dimension);

        double sum = 0.0;
        for (i = 1; i < dimension; ++ i) {
            sum += std::exp((f(i)-f(0)) / scale);
        }

        d(0) = -sum;

        for (i = 1; i < dimension; ++ i) {
            d(i) = std::exp((f(i)-f(0)) / scale);
        }

        return tmp * d;
    }

    // calculate the ARD squared exponential kernel, where thata is the hyper parameter
    inline double ARD_kernel(const VectorXd& x1, const VectorXd& x2, const VectorXd& theta) {
        const unsigned vec_num = x1.rows();

        double sum1 = 0.0;
        auto theta_d1 = theta(vec_num);
        auto theta_d2 = theta(vec_num + 1);

        for (unsigned i = 0; i < vec_num; ++i) {
            sum1 += (x1(i) - x2(i)) * (x1(i) - x2(i)) / (theta(i) * theta(i));
        }
        return theta_d1 * exp(-0.5 * sum1);
    }

    // Kronecker_delta funtion
    inline double Kronecker_delta(double num1, double num2) {
        if (num1 != num2) return 0;
        else return 1;
    }

}
