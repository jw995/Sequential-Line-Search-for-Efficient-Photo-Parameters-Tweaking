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
	// function to calculate miu(·) and sigma^2(·)
    virtual double predict_miu(const Eigen::VectorXd& x) const = 0;
    virtual double predict_sigma_sq(const Eigen::VectorXd& x) const = 0;

    // functions to access data
	virtual const MatrixXd& getX() const = 0;
    virtual const VectorXd& getf() const = 0;
    virtual double get_theta_d1() const = 0;
    virtual double get_theta_d2() const = 0;
    virtual const VectorXd& get_theta() const = 0;

	// functions for GP prior
    static MatrixXd calc_KK(const MatrixXd& X,
                           const double theta_d1, const double theta_d2,
                           const VectorXd& theta);
    static MatrixXd KK_grad_d1(const MatrixXd& X,
                                  const double theta_d1, const double /*theta_d2*/,
                                  const VectorXd& theta);
    static MatrixXd KK_grad_d2(const MatrixXd& X,
                                  const double /*theta_d1*/, const double /*theta_d2*/,
                                  const VectorXd& /*theta*/);
    static MatrixXd KK_grad_theta_i(const MatrixXd& X,
                                    const double theta_d1, const double /*theta_d2*/,
                                    const VectorXd& theta, const unsigned idx);
    static VectorXd calc_k(const VectorXd& x, const MatrixXd& X,
                           const double theta_d1, const double /*theta_d2*/,
                           const VectorXd& theta);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PreferenceRegressor : public Regressor{
public:

    PreferenceRegressor(const Eigen::MatrixXd &X, const std::vector<Preference>& D, bool use_MAP_hyperparameters = false);
    PreferenceRegressor(const Eigen::MatrixXd &X, const std::vector<Preference>& D, const Eigen::VectorXd& w, bool use_MAP_hyperparameters = false);
    PreferenceRegressor(const Eigen::MatrixXd &X, const std::vector<Preference>& D, const Eigen::VectorXd& w, bool use_MAP_hyperparameters, const PreferenceRegressor* previous);

    double predict_miu(const Eigen::VectorXd& x) const override;
    double predict_sigma_sq(const Eigen::VectorXd& x) const override;

    const bool use_MAP_hyperparameters;

    Eigen::VectorXd find_arg_max();

    // Data
    Eigen::MatrixXd         X;
    std::vector<Preference> D;
    Eigen::VectorXd         w; // Weights for calculating the scales in the
                               // BTL model (default = ones), used in
                               // crowdsourcing settings

    // Derived by MAP estimation
    Eigen::VectorXd         f;
    double                  theta_d1;
    double                  theta_d2;
    Eigen::VectorXd         theta;

    // Can be derived after MAP estimation
    Eigen::MatrixXd         K;
    Eigen::MatrixXd         K_inv;

    // IO
    //void dampData(const std::string& dirPath) const;

    const Eigen::MatrixXd& getX() const override { return X; }
    const Eigen::VectorXd& getf() const override { return f; }
    double get_theta_d1() const override { return theta_d1; }
    double get_theta_d2() const override { return theta_d2; }
    const Eigen::VectorXd& get_theta() const override { return theta; }

    struct Params{
        Params() {}
        double theta_d1 = 0.500;
		double theta_d2 = 0.005;
        double theta    = 0.500;
        
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
    GaussianProcessRegressor(const Eigen::MatrixXd &X, const Eigen::VectorXd &f);

    // Specified hyperparameters will be used
    GaussianProcessRegressor(const Eigen::MatrixXd &X, const Eigen::VectorXd &f, 
		double theta_d1, double theta_d2, const Eigen::VectorXd& theta);

    double predict_miu(const Eigen::VectorXd& x) const override;
    double predict_sigma_sq(const Eigen::VectorXd& x) const override;

    // Data
    Eigen::MatrixXd X;
    Eigen::VectorXd f;

    // Derived from MAP or specified directly
    double theta_d1;
    double theta_d2;
    Eigen::VectorXd theta;

    // Can be derived after MAP
    Eigen::MatrixXd K;
    Eigen::MatrixXd K_inv;

    // Getter
    const Eigen::MatrixXd& getX() const override { return X; }
    const Eigen::VectorXd& getf() const override { return f; }
    double get_theta_d1() const override { return theta_d1; }
    double get_theta_d2() const override { return theta_d2; }
    const Eigen::VectorXd& get_theta() const override { return theta; }

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
