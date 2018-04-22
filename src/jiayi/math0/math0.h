#ifndef MATH0_H
#define MATH0_H

// head file for math part

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <math.h>
#include <Eigen/Dense>

////////////////////////////////////////////////
// Gaussian Processes
////////////////////////////////////////////////

// Kronecker_delta funtion
inline double Kronecker_delta(double num1, double num2)
{
	if (num1 != num2) return 0;
	else return 1;
}


// calculate the ARD squared exponential kernel, where thata is the hyper parameter
inline double ARD_kernel(const Eigen::VectorXd& x1, const Eigen::VectorXd& x2, 
	const Eigen::VectorXd& theta, const double thetad_1)
{
	const unsigned vec_num = x1.rows();

	double sum1 = 0.0;
	//double sum2 = 0.0;

	for (unsigned i = 0; i < vec_num; ++i)
	{
		sum1 += (x1(i) - x2(i)) * (x1(i) - x2(i)) / (theta(i) * theta(i));
		//sum2 += Kronecker_delta(x1(i), x2(i));
	}
	// theta_d2 part added later
	//return theta_d1 * exp(-0.5 * sum1) + theta_d2 * sum2;
	return thetad_1 * exp(-0.5 * sum1);

}



 
class GaussianProcess
{
public:
	//Data
	Eigen::VectorXd f;
	Eigen::MatrixXd X;

	Eigen::VectorXd theta;
	double thetad_1;
	double thetad_2;

	Eigen::MatrixXd K;
	Eigen::MatrixXd K_inv;


	// Constructor: Specified hyperparameters will be used
	GaussianProcess::GaussianProcess(const Eigen::MatrixXd &X, const Eigen::VectorXd &f,
		double thetad_1, double thetad_2, const Eigen::VectorXd &theta);

	Eigen::VectorXd calc_k(const Eigen::VectorXd& x);
	Eigen::MatrixXd calc_K(void);

	double estimate_miu(const Eigen::VectorXd& x);
	double estimate_sigma_sq(const Eigen::VectorXd& x);


};



#endif // 
