#include "slider_hy.h"
#include <cmath>
#include <map>
#include "nloptutility.h"
#include "utility.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::pair;
using std::vector;

Slider::Slider(const VectorXd& start, const VectorXd& end, const bool enlarge, const double scale, const double minLength) :
    enlarge(enlarge), minLength(minLength), randStart(start), randEnd(end){
    if (enlarge){
        const auto ends = SliderUtility::enlargeSliderEnds(randStart, randEnd, scale, minLength);
        this->start = ends.first;
        this->end = ends.second;
    }
    else{
        this->start = randStart;
        this->end = randEnd;
    }
}

VectorXd Slider::getValue(const double percent) const{
    return start + percent * (end-start);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace SliderUtility{

    struct Data{
        Data(const VectorXd& c, const VectorXd& r, const double s) : c(c), r(r), s(s) {}
        VectorXd c;
        VectorXd r;
        double   s;
    };

    inline double crop(double x){
        double epsilon = 1e-16;
        double smallVal = (x < 1.0 - epsilon) ? x : (1.0 - epsilon);
        return (x > epsilon) ? smallVal : epsilon;
    }

    inline VectorXd crop(const VectorXd& x){
        VectorXd y(x.rows());
        for (unsigned i = 0; i < x.rows(); ++ i) y(i) = crop(x(i));
        return y;
    }

    double objective(const vector<double> &x, vector<double>& /*grad*/, void* data){
        const double target = static_cast<Data*>(data)->s;
        return - (x[0] - target) * (x[0] - target);
    }

    double constraint_p(const vector<double> &x, vector<double>& /*grad*/, void* data){
        const VectorXd& c = static_cast<Data*>(data)->c;
        const VectorXd& r = static_cast<Data*>(data)->r;
        const double&   t = x[0];

        const VectorXd y = c + t * r;

        double sum = 0.0;
        for (unsigned i = 0; i < y.rows(); ++ i){
            sum += (crop(y(i)) - y(i)) * (crop(y(i)) - y(i));
        }
        return sum;
    }

    double constraint_n(const vector<double> &x, vector<double>& /*grad*/, void* data){
        const VectorXd& c = static_cast<Data*>(data)->c;
        const VectorXd& r = static_cast<Data*>(data)->r;
        const double&   t = x[0];

        const VectorXd y = c - t * r;

        double sum = 0.0;
        for (unsigned i = 0; i < y.rows(); ++ i){
            sum += (crop(y(i)) - y(i)) * (crop(y(i)) - y(i));
        }
        return sum;
    }

    pair<VectorXd, VectorXd> enlargeSliderEnds(const VectorXd& x1, const VectorXd& x2, const double scale, const double minLength){
        const VectorXd c = 0.5 * (crop(x1) + crop(x2));
        const VectorXd r = crop(x1) - c;

        auto data = std::make_shared<Data>(c, r, scale);

        const double t1 = nloptUtility::compute(VectorXd::Constant(1, 1.0), VectorXd::Constant(1, scale), VectorXd::Constant(1, 0.0), objective, constraint_p, data.get(), nlopt::LN_COBYLA, 1000)(0);
        const double t2 = nloptUtility::compute(VectorXd::Constant(1, 1.0), VectorXd::Constant(1, scale), VectorXd::Constant(1, 0.0), objective, constraint_n, data.get(), nlopt::LN_COBYLA, 1000)(0);

        const VectorXd x1New = crop(c + t1 * r);
        const VectorXd x2New = crop(c - t2 * r);

        const double length = (x1New - x2New).norm();

        if (length < minLength){
            if (std::abs(t1 - t2) < 1e-10){
                return pair<VectorXd, VectorXd>(c + (minLength / length) * t1 * r, c - (minLength / length) * t2 * r);
            }
            else if (t1 > t2){
                return pair<VectorXd, VectorXd>(c + 2.0 * (minLength / length) * t1 * r, c - t2 * r);
            }
            else{
                return pair<VectorXd, VectorXd>(c + t1 * r, c - 2.0 * (minLength / length) * t2 * r);
            }
        }
        return pair<VectorXd, VectorXd>(x1New, x2New);
    }

    void mergeData(Eigen::MatrixXd &X, std::vector<Preference> &D, const double epsilon){
        const double epsSquared = epsilon * epsilon;

        while (true){
            bool dirty = false;

            const unsigned N = X.rows();
            const unsigned M = X.cols();

            // Distance matrix (upper triangle only)
            MatrixXd Dist(M, M);
            for (unsigned i = 0; i < M; ++ i){
                for (unsigned j = i + 1; j < M; ++ j){
                    Dist(i, j) = (X.col(i) - X.col(j)).squaredNorm();
                }
            }

            for (unsigned i = 0; i < M; ++ i){
                for (unsigned j = i + 1; j < M; ++ j){
                    if (!dirty && Dist(i, j) < epsSquared){
                        // Construct a mapping from the old indices to the new one
                        std::map<unsigned, unsigned> mapping;
                        unsigned newIndex = 0;
                        for (unsigned oldIndex = 0; oldIndex < M; ++ oldIndex){
                            if (oldIndex != i && oldIndex != j){
                                mapping[oldIndex] = newIndex ++;
                            }
                        }
                        mapping[i] = M - 2;
                        mapping[j] = M - 2;

                        // Update the matrix
                        MatrixXd newX(N, M - 1);
                        for (unsigned oldIndex = 0; oldIndex < M; ++ oldIndex){
                            newX.col(mapping[oldIndex]) = X.col(oldIndex);
                        }
                        newX.col(M - 2) = 0.5 * (X.col(i) + X.col(j));
                        X = newX;

                        // Update the indices in the preference pairs
                        for (Preference& p : D){
                            for (unsigned i = 0; i < p.size(); ++ i) p[i] = mapping[p[i]];
                        }

                        dirty = true;
                    }
                }
            }
            if (!dirty) return;
        }
    }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace SliceSampler{

    VectorXd sampling(Func func, const void* data, const VectorXd &xLast, const Eigen::VectorXd &bracketSize){
        const unsigned dim = xLast.rows();
        const double   y   = Utility::generateUniformReal() * func(xLast, data);

        const VectorXd v = bracketSize.cwiseProduct(Utility::generateRandomVector(dim));

        // Set initial hyperrectangle
        VectorXd l = xLast - v;
        VectorXd u = xLast + bracketSize;

        VectorXd xNext;
        while (true){
            const VectorXd xCand = l + (u - l).cwiseProduct(Utility::generateRandomVector(dim));
            const double   yCand = func(xCand, data);

            if (yCand > y){
                xNext = xCand;
                break;
            }
            else{
                // Narrow hyperrectangle
                for (unsigned i = 0; i < dim; ++ i){
                    if (xLast(i) < xCand(i)){
                        u(i) = xCand(i);
                    }
                    else{
                        l(i) = xCand(i);
                    }
                }
            }
        }
        return xNext;
    }
}