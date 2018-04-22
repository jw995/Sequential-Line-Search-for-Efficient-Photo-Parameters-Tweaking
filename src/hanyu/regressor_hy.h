#ifndef REGRESSOR_H
#define REGRESSOR_H

#include <Eigen/Core>
#include <vector>
#include <string>
#include <utility>
#include "regressor_hy.h"
#include "preference.h"
#include <memory>


using Eigen::MatrixXd;
using Eigen::VectorXd;

// original:
//     regressor, 
//     preferenceregressor
//     gaussianprocessregressor
//     expectedimprovementmaximizer
// is contained in this file

class Regressor{
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PreferenceRegressor : public Regressor{
public:

    PreferenceRegressor(const Eigen::MatrixXd &X, const std::vector<Preference>& D, bool use_MAP_hyperparameters = false);
    PreferenceRegressor(const Eigen::MatrixXd &X, const std::vector<Preference>& D, const Eigen::VectorXd& w, bool use_MAP_hyperparameters = false);
    PreferenceRegressor(const Eigen::MatrixXd &X, const std::vector<Preference>& D, const Eigen::VectorXd& w, bool use_MAP_hyperparameters, const PreferenceRegressor* previous);

    double predict_y(const Eigen::VectorXd& x) const override;
    double predict_sigma(const Eigen::VectorXd& x) const override;

    const bool use_MAP_hyperparameters;

    Eigen::VectorXd find_arg_max();

    // Data
    Eigen::MatrixXd         X;
    std::vector<Preference> D;
    Eigen::VectorXd         w; // Weights for calculating the scales in the
                               // BTL model (default = ones), used in
                               // crowdsourcing settings

    // Derived by MAP estimation
    Eigen::VectorXd         y;
    double                  a;
    double                  b;
    Eigen::VectorXd         r;

    // Can be derived after MAP estimation
    Eigen::MatrixXd         C;
    Eigen::MatrixXd         C_inv;

    // IO
    //void dampData(const std::string& dirPath) const;

    const Eigen::MatrixXd& getX() const override { return X; }
    const Eigen::VectorXd& gety() const override { return y; }
    double geta() const override { return a; }
    double getb() const override { return b; }
    const Eigen::VectorXd& getr() const override { return r; }

    struct Params{
        Params() {}
        double a         = 0.500;
        double r         = 0.500;
        double b         = 0.005;
        double variance  = 0.250; // Used when hyperparameters are estimated via MAP
        double btl_scale = 0.010;
        static Params& getInstance() { static Params p; return p; }
    };

private:
    void compute_MAP(const PreferenceRegressor* = nullptr);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GaussianProcessRegressor : public Regressor{
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Regressor;

namespace ExpectedImprovement{
    double calculateExpectedImprovedment(const Regressor& regressor, const Eigen::VectorXd &x);
    Eigen::VectorXd findNextPoint(Regressor &regressor);
    std::vector<Eigen::VectorXd> findNextPoints(const Regressor &regressor, unsigned n);
}

#endif // REGRESSOR_H
