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
	//����ϵ��
	float spring_constant;
	//����ԭ��
	float original_length;
	//����ϵ��
	float damping_factor;
};


