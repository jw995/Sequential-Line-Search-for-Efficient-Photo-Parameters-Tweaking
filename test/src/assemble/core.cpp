#include "core.h"
#include <iostream>
#include <cmath>
#include "utility.h"
#include "sliderutility.h"
#include "expectedimprovementmaximizer.h"
#include "preferenceregressor.h"

namespace
{
    constexpr unsigned dimension = 6;
}

using Eigen::MatrixXd;
using Eigen::VectorXd;

Core::Core() : use_MAP_hyperparameters(false) {
    X = MatrixXd::Zero(0, 0);
    D.clear();

    x_max = VectorXd::Zero(0);
    y_max = NAN;
}

void Core::proceedOptimization(double slider_position) {
    // Add new preference data
    const VectorXd x = computeParametersFromSlider(slider_position);
    addData(std::vector<VectorXd>{ x, slider->orig_0, slider->orig_1 });

    // Compute regression
    computeRegression();

    // Check the current best
    x_max = regressor->find_arg_max();
    y_max = regressor->predict_y(x_max);

    // Update slider ends
    updateSliderEnds();
}

void Core::addData(const VectorXd &x1, const VectorXd &x2) {
    addData(std::vector<Eigen::VectorXd>{x1, x2});
}

void Core::addData(const Eigen::VectorXd &x1, const Eigen::VectorXd &x2, const Eigen::VectorXd &x3) {
    addData(std::vector<Eigen::VectorXd>{x1, x2, x3});
}

void Core::addData(const std::vector<Eigen::VectorXd> &xs) {
    if (X.rows() == 0) {
        this->X = MatrixXd(xs[0].rows(), xs.size());
        for (unsigned i = 0; i < xs.size(); ++ i) X.col(i) = xs[i];
        std::vector<unsigned> indices(xs.size());
        for (unsigned i = 0; i < xs.size(); ++ i) indices[i] = i;
        D.push_back(Preference(indices));
        return;
    }

    const unsigned d = X.rows();
    const unsigned N = X.cols();

    MatrixXd newX(d, N + xs.size());
    newX.block(0, 0, d, N) = X;
    for (unsigned i = 0; i < xs.size(); ++ i) newX.col(N + i) = xs[i];
    this->X = newX;

    std::vector<unsigned> indices(xs.size());
    for (unsigned i = 0; i < xs.size(); ++ i) indices[i] = N + i;
    D.push_back(Preference(indices));

    SliderUtility::mergeData(X, D, 5e-03);
}

double Core::evaluateObjectiveFunction(const Eigen::VectorXd& x) const {
    assert(x.rows() == dimension);

    auto lambda = [](const Eigen::VectorXd& x, const Eigen::VectorXd& mu, const double sigma) {
        return std::exp(- (x - mu).squaredNorm() / (sigma * sigma));
    };

    return lambda(x, Eigen::VectorXd::Constant(dimension, 0.5), 1.0);
}

void Core::computeRegression() {
    regressor = std::make_shared<PreferenceRegressor>(X, D, use_MAP_hyperparameters);
}

void Core::updateSliderEnds() {
    // if first time, generate random slider ends
    if (slider.get() == nullptr) {
        slider = std::make_shared<Slider>(Utility::generateRandomVector(dimension), Utility::generateRandomVector(dimension), false);
        return;
    }

    const VectorXd x_1 = regressor->find_arg_max();
    const VectorXd x_2 = ExpectedImprovement::findNextPoint(*regressor);

    slider = std::make_shared<Slider>(x_1, x_2, true);
}


void Core::updateSliderEnds(VectorXd &start, VectorXd &end)
{
    //if first time, generate random slider ends
    if (slider.get() == nullptr) {
        slider = std::make_shared<Slider>(Utility::generateRandomVector(dimension), Utility::generateRandomVector(dimension), false);
        return;
    }

    const VectorXd x_1 = regressor->find_arg_max();
    const VectorXd x_2 = ExpectedImprovement::findNextPoint(*regressor);

    start = x_1;
    end = x_2;
}

VectorXd Core::computeParametersFromSlider(double value) const {
    assert(slider.get() != nullptr);
    return slider->getValue(value);
}
