#pragma once
#include <math.h>
#include <eigen3/Eigen/Dense>

constexpr double pi() { return std::atan(1)*4; }
constexpr float t1 = 30/180.0*pi();
constexpr float t2 = t1 + 120/180.0*pi();
constexpr float t3 = t2 + 120/180.0*pi();

constexpr float L = 1;

void get_J(Eigen::Matrix3f& J, float t ){
	J << ( cos(t3+t)-cos(t2+t) ), ( cos(t1+t)-cos(t3+t) ), ( cos(t2+t)-cos(t1+t) ),
		 ( sin(t3+t)-sin(t2+t) ), ( sin(t1+t)-sin(t3+t) ), ( sin(t2+t)-sin(t1+t) ),
		 (sin(t2-t3))/L, (-sin(t1-t3))/L, (sin(t1-t2))/L;
	J = J/(sin(t1 - t2) - sin(t1 - t3) + sin(t2 - t3));
}

void get_Jinv(Eigen::Matrix3f& Jinv, float t ){
	Jinv << -sin(t1+t), cos(t1+t), L,
			-sin(t2+t), cos(t2+t), L,
			-sin(t3+t), cos(t3+t), L;
}
