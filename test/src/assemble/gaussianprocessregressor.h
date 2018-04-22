#ifndef GAUSSIANPROCESSREGRESSOR_H
#define GAUSSIANPROCESSREGRESSOR_H

#include <Eigen/Core>
#include "regressor.h"

class GaussianProcessRegressor : public Regressor
{
public:
    // Hyperparameters will be set via MAP estimation
    GaussianProcessRegressor(const Eigen::MatrixXd &X, const Eigen::VectorXd &y);

    // Specified hyperparameters will be used
    GaussianProcessRegressor(const Eigen::MatrixXd &X, const Eigen::VectorXd &y, double a, double b, const Eigen::VectorXd& r);

    double predict_y(const Eigen::VectorXd& x) const override;
    double predict_sigma(const Eigen::VectorXd& x) const override;

    // Data
    Eigen::MatrixXd X;
    Eigen::VectorXd y;

    // Derived from MAP or specified directly
    double a;
    double b;
    Eigen::VectorXd r;

    // Can be derived after MAP
    Eigen::MatrixXd C;
    Eigen::MatrixXd C_inv;

    // Getter
    const Eigen::MatrixXd& getX() const override { return X; }
    const Eigen::VectorXd& gety() const override { return y; }
    double geta() const override { return a; }
    double getb() const override { return b; }
    const Eigen::VectorXd& getr() const override { return r; }

private:
    void compute_MAP();
};

#endif // GAUSSIANPROCESSREGRESSOR_H
