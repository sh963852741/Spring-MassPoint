#include "Spring.h"

Spring::Spring(MassPoint& point1, MassPoint& point2):point_1(point1), point_2(point2)
{
	spring_constant = (float)0.2;
	original_length = (float)0.02;
	damping_factor = (float)0.5;
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
