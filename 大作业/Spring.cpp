#include "Spring.h"

Spring::Spring(MassPoint& point1, MassPoint& point2, float spring_constant, float damping_factor)
	:point_1(point1), point_2(point2)
{

	this->spring_constant = spring_constant;
	original_length = (point1.positon - point2.positon).norm();
	this->damping_factor = damping_factor;
}
Spring::Spring(MassPoint& point1, MassPoint& point2, float length, float spring_constant, float damping_factor)
	:point_1(point1), point_2(point2)
{
	this->spring_constant = spring_constant;
	original_length = length;
	this->damping_factor = damping_factor;
}
void Spring::CalcAndAppForce()
{
	Vector3f springVector = point_1.positon - point_2.positon;
	// 两点距离
	float length = springVector.norm();

	Vector3f force = Vector3f(0, 0, 0);
	//计算施加于质点上的力
	if (length != 0)force += springVector.normalized() * (length - original_length) * (-spring_constant); //弹性系数*方向*deltaX
	//减掉阻尼
	//force -= springVector.normalized() * springVector.normalized().dot(point_1.velocity - point_2.velocity) * damping_factor; //阻尼需要做投影
	force -= (point_1.velocity - point_2.velocity) * damping_factor; //阻尼需要做投影吗

	point_1.AddForce(force);
	point_2.AddForce(-force);
}

// 浅拷贝
//Spring::Spring(const Spring& spring) :point_1(spring.point_1), point_2(spring.point_2)
//{
//	spring_constant = 0.2;
//	original_length = 0.02;
//	damping_factor = 0.5;
//}

//Spring& Spring::operator=(const Spring&& spring)
//{
//	Spring& s =*new Spring(spring.point_1, spring.point_2);
//	return s;
//}
