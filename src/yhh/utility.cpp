#include "utility.h"
#include <random>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <Eigen/Core>

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace
{
std::random_device seed;
std::default_random_engine gen(seed());
std::uniform_real_distribution<double> uniform_dist(0.0, 1.0);
std::normal_distribution<> normal_dist(0.0, 1.0);
}

namespace Utility
{

Eigen::VectorXd generateRandomVector(unsigned n)
{
    Eigen::VectorXd x(n);
    for (unsigned i = 0; i < n; ++ i)
    {
        x(i) = uniform_dist(gen);
    }
    return x;
}

double generateUniformReal()
{
    return uniform_dist(gen);
}

double generateStandardNormal()
{
    return normal_dist(gen);
}

double temp(const Eigen::VectorXd& x, const void* data)
{
    const MatrixXd& Sigma_inv = static_cast<const std::pair<MatrixXd, double>*>(data)->first;
    const double    Sigma_det = static_cast<const std::pair<MatrixXd, double>*>(data)->second;
    return Utility::gauss(x, VectorXd::Zero(x.rows()), Sigma_inv, Sigma_det);
}

VectorXd generateNormal(const Eigen::VectorXd &mu, const Eigen::MatrixXd &Sigma)
{
    VectorXd x = VectorXd::Zero(mu.rows());
    std::pair<MatrixXd, double> data(Sigma.inverse(), Sigma.determinant());
    x = Utility::sampling(temp, &data, x, VectorXd::Constant(x.rows(), Sigma.maxCoeff() * 3.0));
    x = Utility::sampling(temp, &data, x, VectorXd::Constant(x.rows(), Sigma.maxCoeff() * 3.0));
    x = Utility::sampling(temp, &data, x, VectorXd::Constant(x.rows(), Sigma.maxCoeff() * 3.0));
    x = Utility::sampling(temp, &data, x, VectorXd::Constant(x.rows(), Sigma.maxCoeff() * 3.0));
    x = Utility::sampling(temp, &data, x, VectorXd::Constant(x.rows(), Sigma.maxCoeff() * 3.0));
    return x + mu;
}

void exportMatrixToCsv(const std::string& filePath, const Eigen::MatrixXd& X)
{
    std::ofstream ofs(filePath);
    for (unsigned i = 0; i < X.rows(); ++ i)
    {
        for (unsigned j = 0; j < X.cols(); ++ j)
        {
            ofs << X(i, j);
            if (j + 1 != X.cols()) ofs << ",";
        }
        ofs << std::endl;
    }
}

std::string getCurrentTimeInString()
{
    const std::time_t t = std::time(nullptr);
    std::stringstream s; s << std::put_time(std::localtime(&t), "%Y%m%d%H%M%S");
    return s.str();
}


VectorXd sampling(Func func, const void* data, const VectorXd &x_last, const Eigen::VectorXd &bracket_size)
{
	const unsigned dim = x_last.rows();
	const double   y = Utility::generateUniformReal() * func(x_last, data);

	const VectorXd v = bracket_size.cwiseProduct(Utility::generateRandomVector(dim));

	// Set initial hyperrectangle
	VectorXd l = x_last - v;
	VectorXd u = x_last + bracket_size;

	VectorXd x_next;
	while (true)
	{
		const VectorXd x_cand = l + (u - l).cwiseProduct(Utility::generateRandomVector(dim));
		const double   y_cand = func(x_cand, data);

		if (y_cand > y)
		{
			x_next = x_cand;
			break;
		}
		else
		{
			// Narrow hyperrectangle
			for (unsigned i = 0; i < dim; ++i)
			{
				if (x_last(i) < x_cand(i))
				{
					u(i) = x_cand(i);
				}
				else
				{
					l(i) = x_cand(i);
				}
			}
		}
	}
	return x_next;
}

}