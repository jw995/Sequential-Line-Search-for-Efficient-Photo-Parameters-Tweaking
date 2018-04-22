#ifndef SLIDER_H
#define SLIDER_H

// original:
//     slider, 
//     sliderutility 
//     slicesampler
// is contained in this file

#include <Eigen/Core>
#include <utility>
#include "preference.h"

class Slider{
public:
    Slider(const Eigen::VectorXd& start, const Eigen::VectorXd& end, const bool enlarge, const double scale = 1.25, const double minLength = 0.25);

    Eigen::VectorXd getValue(const double percent) const;

    const bool   enlarge;
    const double minLength;

    Eigen::VectorXd start;
    Eigen::VectorXd end;

    Eigen::VectorXd randStart;
    Eigen::VectorXd randEnd;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace SliderUtility{
std::pair<Eigen::VectorXd, Eigen::VectorXd> enlargeSliderEnds(const Eigen::VectorXd& x1, const Eigen::VectorXd& x2, const double scale = 1.25, const double minLength = 1e-10);
void mergeData(Eigen::MatrixXd& X, std::vector<Preference>& D, const double epsilon = 5e-03);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace SliceSampler{
typedef double (*Func)(const Eigen::VectorXd& x, const void* data);
Eigen::VectorXd sampling(Func func, const void* data, const Eigen::VectorXd& xLast, const Eigen::VectorXd& bracketSize);
}

#endif // SLIDER_H