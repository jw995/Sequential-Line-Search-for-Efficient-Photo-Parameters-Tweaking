#include "core.h"
#include <iostream>
#include <cmath>
#include "utility.h"
#include "slider_hy.h"
#include "regressor_hy.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace
{
    constexpr unsigned dimension = 6;
}

Core::Core() : useMAPHyperparams(false) {
    X = MatrixXd::Zero(0, 0);
    D.clear();

    x_max = VectorXd::Zero(0);
    y_max = NAN;
}

void Core::proceedOptimization(double slider_position) {
    // Add new preference data
    const VectorXd x = computeParametersFromSlider(slider_position);
    addData(std::vector <VectorXd> {x, slider->randStart, slider->randEnd});

    // Compute regression
    computeRegression();

    // Check the current best
    x_max = regressor->find_arg_max();
    y_max = regressor->predict_miu(x_max);

    // Update slider ends
    updateSliderEnds();
}

void Core::addData(const VectorXd &x1, const VectorXd &x2) {
    addData(std::vector <Eigen::VectorXd> {x1, x2});
}

void Core::addData(const Eigen::VectorXd &x1,
                   const Eigen::VectorXd &x2,
                   const Eigen::VectorXd &x3) {
    addData(std::vector <Eigen::VectorXd> {x1, x2, x3});
}

void Core::addData(const std::vector <Eigen::VectorXd> &x) {
    unsigned i;
    std::vector <unsigned> idx(x.size());
    if (X.rows() == 0) {
        this->X = MatrixXd(x[0].rows(), x.size());
        //std::vector <unsigned> idx(x.size());

        for (i = 0; i < x.size(); ++i) {
            X.col(i) = x[i];
        }
        for (i = 0; i < x.size(); ++i) {
            idx[i] = i;
        }

        D.push_back(Preference(idx));
        return;
    }

    const unsigned d = X.rows();
    const unsigned N = X.cols();
    //std::vector <unsigned> idx(x.size());

    MatrixXd newX(d, N+x.size());
    newX.block(0, 0, d, N) = X;
    for (i = 0; i < x.size(); ++i) {
        newX.col(N + i) = x[i];
    }
    this->X = newX;

    for (i = 0; i < x.size(); ++ i) {
        idx[i] = N + i;
    }
    D.push_back(Preference(idx));
    SliderUtility::mergeData(X, D, 5e-03);
}

void Core::computeRegression() {
    regressor = std::make_shared <PreferenceRegressor> (X, D, useMAPHyperparams);
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

void Core::updateSliderEnds(VectorXd &start, VectorXd &end) {
    // if first time, generate random slider ends
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