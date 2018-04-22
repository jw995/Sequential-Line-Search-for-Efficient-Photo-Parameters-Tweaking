#ifndef CORE_H
#define CORE_H

#include <vector>
#include <memory>
#include <Eigen/Core>
#include "preference.h"
#include "slider.h"

class PreferenceRegressor;

class Core
{
public:
    Core();

    std::shared_ptr <PreferenceRegressor> regressor;

    bool use_MAP_hyperparameters;

    Eigen::MatrixXd         X;  // parameters
    std::vector<Preference> D;  // {x_chosen, x+, xEI} sets

    double evaluateObjectiveFunction(const Eigen::VectorXd &x) const;

    void clear() {
        X = Eigen::MatrixXd::Zero(0, 0);
        D.clear();
        x_max = Eigen::VectorXd::Zero(0);
        regressor = nullptr;
        slider    = nullptr;
    }

    // For optimization
    void proceedOptimization(double slider_position);
    Eigen::VectorXd x_max;
    double          y_max;

    // For regression
    void addData(const Eigen::VectorXd& x1, const Eigen::VectorXd &x2);
    void addData(const Eigen::VectorXd& x1, const Eigen::VectorXd &x2, const Eigen::VectorXd &x3);
    void addData(const std::vector<Eigen::VectorXd>& xs);
    void computeRegression();

    // For slider management
    void updateSliderEnds();
    void updateSliderEnds(Eigen::VectorXd &start, Eigen::VectorXd &end);
    std::shared_ptr<Slider> slider;
    Eigen::VectorXd computeParametersFromSlider(double value) const;
};

#endif // CORE_H
