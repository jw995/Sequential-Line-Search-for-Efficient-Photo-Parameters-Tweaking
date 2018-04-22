#ifndef REGRESSOR_H
#define REGRESSOR_H

#include <Eigen/Core>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Regressor
{
public:
    virtual double predict_y(const Eigen::VectorXd& x) const = 0;
    virtual double predict_sigma(const Eigen::VectorXd& x) const = 0;

    virtual const MatrixXd& getX() const = 0;
    virtual const VectorXd& gety() const = 0;
    virtual double geta() const = 0;
    virtual double getb() const = 0;
    virtual const VectorXd& getr() const = 0;

    static MatrixXd calc_C(const MatrixXd& X,
                           const double a, const double b,
                           const VectorXd& r);
    static MatrixXd calc_C_grad_a(const MatrixXd& X,
                                  const double a, const double /*b*/,
                                  const VectorXd& r);
    static MatrixXd calc_C_grad_b(const MatrixXd& X,
                                  const double /*a*/, const double /*b*/,
                                  const VectorXd& /*r*/);
    static MatrixXd calc_C_grad_r_i(const MatrixXd& X,
                                    const double a, const double /*b*/,
                                    const VectorXd& r, const unsigned index);
    static VectorXd calc_k(const VectorXd& x, const MatrixXd& X,
                           const double a, const double /*b*/,
                           const VectorXd& r);
};

#endif // REGRESSOR_H
