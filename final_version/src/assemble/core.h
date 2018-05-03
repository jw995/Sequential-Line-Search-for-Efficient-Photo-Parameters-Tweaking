#ifndef CORE_H
#define CORE_H

#include <vector>
#include <memory>
#include <Eigen/Core>
#include "preference.h"
#include "slider_hy.h"

class PreferenceRegressor;

class Core
{
public:
    Core();

    std::shared_ptr <PreferenceRegressor> regressor;

    bool useMAPHyperparams;

    Eigen::MatrixXd         X;  // parameters
    std::vector <Preference> D;  // {x_chosen, x+, xEI} sets


    void clear() {
        X = Eigen::MatrixXd::Zero(0, 0);
        D.clear();
        x_max = Eigen::VectorXd::Zero(0);
        regressor = nullptr;
        slider    = nullptr;
    }

    // Optimization
    void proceedOptimization(double slider_position);
    Eigen::VectorXd x_max;
    double          y_max;

    // Regression
    void addData(const Eigen::VectorXd& x1, const Eigen::VectorXd &x2);
    void addData(const Eigen::VectorXd& x1, const Eigen::VectorXd &x2, const Eigen::VectorXd &x3);
    void addData(const std::vector<Eigen::VectorXd>& xs);
    void computeRegression();

    // Slider management
    void updateSliderEnds();
    void updateSliderEnds(Eigen::VectorXd &start, Eigen::VectorXd &end);
    std::shared_ptr<Slider> slider;
    Eigen::VectorXd computeParametersFromSlider(double value) const;
};

#endif // CORE_H
