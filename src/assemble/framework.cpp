#include <vector>
#include <Eigen/Dense>


std::vector<Eigen::VectorXd> math(Eigen::VectorXd userChoosed){
	std::vector <Eigen::VectorXd> barNodes;
 	Eigen::VectorXd barStart(6);
	Eigen::VectorXd barEnd(6);

    barStart(0) = userChoosed(0) - 3;
    barStart(1) = userChoosed(1) - 3;
    barStart(2) = userChoosed(2) - 3;
    barStart(3) = userChoosed(3) - 3;
    barStart(4) = userChoosed(4) - 3;
    barStart(5) = userChoosed(5) - 3;

    barEnd(0) = userChoosed(0) + 5;
    barEnd(1) = userChoosed(1) + 5;
    barEnd(2) = userChoosed(2) + 5;
    barEnd(3) = userChoosed(3) + 5;
    barEnd(4) = userChoosed(4) + 5;
    barEnd(5) = userChoosed(5) + 5;


	barNodes.push_back(barStart);
	barNodes.push_back(barEnd);

	return barNodes;
}

Eigen::VectorXd bar(std::vector<Eigen::VectorXd> X){
	Eigen::VectorXd userChoosed(6);
	Eigen::VectorXd X1 = X[0];
	Eigen::VectorXd X2 = X[1];

	userChoosed = (X[1] - X[0]) * 0.5;


	return userChoosed;

}

int main(){

	int terminate = 0;

	Eigen::VectorXd start(6);

	start(0) = (double) rand()/RAND_MAX;
    start(1) = (double) rand()/RAND_MAX;
    start(2) = (double) rand()/RAND_MAX;
    start(3) = (double) rand()/RAND_MAX;
    start(4) = (double) rand()/RAND_MAX;
    start(5) = (double) rand()/RAND_MAX;

	auto userChoosed = start;
	printf("%f, %f, %f, %f, %f, %f\n", start(0), start(1), start(2), start(3), start(4), start(5));

	while(terminate != 1){

		auto barPos = math(userChoosed);
		printf("%f, %f, %f, %f, %f, %f\n", barPos[0](0), barPos[0](1), barPos[0](2), barPos[0](3), barPos[0](4), barPos[0](5));
		auto userChoosed = bar(barPos);
		printf("%f, %f, %f, %f, %f, %f\n", userChoosed(0), userChoosed(1), userChoosed(2), userChoosed(3), userChoosed(4), userChoosed(5));


		terminate = 1;
	}




	return 0;
}