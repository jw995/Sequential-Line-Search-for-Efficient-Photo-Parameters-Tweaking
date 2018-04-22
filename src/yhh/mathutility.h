#ifndef MATHUTILITY_H
#define MATHUTILITY_H

#include <Eigen/Core>

using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace MathUtility
{
    VectorXd calc_k(const VectorXd& x, const MatrixXd& X, const VectorXd& theta);
    MatrixXd calc_K(const MatrixXd& X, const VectorXd& theta);
    VectorXd generateRandomVector(unsigned n);

    // Normal and Log-Normal distribution
    inline double normal(double x, double mu, double sigmasquare);
    inline double logNormal(double x, double mu, double sigmasquared);

    // BTL and its derivative
    inline double BTL(VectorXd f, double scale);
    inline VectorXd dBTL(const VectorXd& f, double scale);

    // Evaluate ARD squared exponential kernel and Kronecker_delta function
    inline double ARD_kernel(const VectorXd& x1, const VectorXd& x2, const VectorXd& theta);
    inline double Kronecker_delta(double num1, double num2);

}
#endif  // MATHUTILITY_H
