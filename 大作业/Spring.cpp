#include "Spring.h"

Spring::Spring(MassPoint& point1, MassPoint& point2, float spring_constant, float damping_factor)
	:point_1(point1), point_2(point2)
{

	this->spring_constant = spring_constant;
	original_length = (point1.positon - point2.positon).norm();
	this->damping_factor = damping_factor;
}
void Spring::CalcAndAppForce()
{
	Vector3f springVector = point_1.positon - point_2.positon;
	// �������
	float length = springVector.norm();

	Vector3f force = Vector3f(0, 0, 0);
	//����ʩ�����ʵ��ϵ���
	if (length != 0)force += springVector.normalized() * (length - original_length) * (-spring_constant); //����ϵ��*����*deltaX
	//��������
	force -= (point_1.velocity - point_2.velocity) * damping_factor; //Ӧ����ͶӰ����ʡ��

	point_1.AddForce(force);
	point_2.AddForce(-force);
}

// ǳ����
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
