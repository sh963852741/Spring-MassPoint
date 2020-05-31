#include "SMSystem.h"

SMSystem::SMSystem() :mass_point_arr(nullptr), spring_arr(nullptr)
{
}

SMSystem::~SMSystem()
{
	if (spring_arr != nullptr)delete spring_arr;
	if (mass_point_arr != nullptr)delete mass_point_arr;
}

void SMSystem::Simulate()
{
	CalcSpring();
	//AddGlobleForce();
	mass_point_arr[0].AddForce(Vector3f((float)0.1, 0, 0));
	CalcPoint();
}

void SMSystem::MakeTestSurface()
{
	mass_point_arr = (MassPoint*)operator new (sizeof(MassPoint) * 50);
	spring_arr = (Spring*)operator new (sizeof(Spring) * 49);
	for (int i = 0; i < 50; ++i)
	{
		mass_point_arr[i] = MassPoint(Vector3f(0, (float)(0.8 - i * 0.02), -1));
	}
	for (int i = 0; i < 49; ++i)
	{
		Spring s = Spring(mass_point_arr[i], mass_point_arr[i + 1]);
		memcpy_s(&spring_arr[i], sizeof(Spring), &s, sizeof(Spring));
		//spring_arr[i] = Spring(mass_point_arr[i], mass_point_arr[i + 1]);
	}
}

void SMSystem::DrawWireframe()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int i = 0; i < 50; ++i)
	{
		glVertex3f(mass_point_arr[i].positon[0], mass_point_arr[i].positon[1], mass_point_arr[i].positon[2]);
	}
	glEnd();
	glFlush();
}

void SMSystem::AddPoint(Vector3f positon, float mass)
{
	mass_point_arr[current_point_index++] = MassPoint(positon, mass);
}

void SMSystem::AddSpring(int p1_index, int p2_index)
{
	Spring s = Spring(mass_point_arr[p1_index], mass_point_arr[p2_index]);
	memcpy_s(&spring_arr[current_spring_index++], sizeof(Spring), &s, sizeof(Spring));
}

void SMSystem::CalcPoint()
{
	for (int i = 0; i < 50; ++i)
	{
		mass_point_arr[i].Update((float)0.0001);
	}
}

void SMSystem::CalcSpring()
{
	for (int i = 0; i < 49; ++i)
	{
		spring_arr[i].CalcAndAppForce();
	}
}


