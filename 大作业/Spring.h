#pragma once
#include <Eigen/Core>
#include "MassPoint.h"
using namespace std;
using namespace Eigen;
class Spring
{
public:
	Spring(MassPoint& point1, MassPoint& point2, float spring_constant = 0.8, float damping_factor = 0.05);
	Spring(MassPoint& point1, MassPoint& point2, float length, float spring_constant, float damping_factor);
	//Spring(Spring&& spring);
	MassPoint& point_1;
	MassPoint& point_2;
	void CalcAndAppForce();
	//Spring(const Spring& spring);
	//Spring& operator=(const Spring&& spring);
private:
	//弹簧系数
	float spring_constant;
	//弹簧原长
	float original_length;
	//阻尼系数
	float damping_factor;
};


