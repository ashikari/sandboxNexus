#include "kinematics.hpp"
#include <iostream>
#include <eigen3/Eigen/Dense>

int main(){
	Eigen::Matrix3f J,J_inv;
	float t = 0;
	get_J(J, t);
	get_Jinv(J_inv,t);
	std::cout<<J*J_inv<<std::endl;

	std::cout<<J_inv(0,0)<<std::endl;

	return 0;
}
