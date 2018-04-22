// source file for math0

#include "math0.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <Eigen/LU>

using Eigen::MatrixXd;
using Eigen::VectorXd;

GaussianProcess::GaussianProcess(const MatrixXd &X, const VectorXd &f, 
	double thetad_1, double thetad_2, const VectorXd &theta)
{
	this->X = X;
	this->f = f;
	this->thetad_1 = thetad_1;
	this->thetad_2 = thetad_2;
	this->theta = theta;

	K = calc_K();
	K_inv = K.inverse();
}

VectorXd GaussianProcess::calc_k(const VectorXd& x)
{
	// X is the matrix that contains x'
	// each column of X is a x'

	const unsigned num = X.cols();

	VectorXd k(num);
	for (unsigned i = 0; i < num; ++i)
	{
		k(i) = ARD_kernel(x, X.col(i), theta, thetad_1);
	}

	return k;
}

MatrixXd GaussianProcess::calc_K(void)
{
	const unsigned num = X.cols();
	//const unsigned vec_num = theta.rows();

	MatrixXd C(num, num);
	for (unsigned i = 0; i < num; ++i)
	{
		for (unsigned j = i; j < num; ++j)
		{
			const double value = ARD_kernel(X.col(i), X.col(j), theta, thetad_1);
			C(i, j) = value;
			C(j, i) = value;
		}
	}
	
	return C + thetad_2 * MatrixXd::Identity(num, num);
	// adding the element theta_d2*kronecker_delta in ARD_kerel here as an identity matrix
}


double GaussianProcess::estimate_miu(const VectorXd& x)
{
	VectorXd k = calc_k(x);
	return k.transpose() * K_inv * f;
}

double GaussianProcess::estimate_sigma_sq(const VectorXd& x)
{
	VectorXd k = calc_k(x);
	return std::sqrt(thetad_1 + thetad_2 - k.transpose() * K_inv * k);
}


