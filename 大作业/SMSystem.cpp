#include "SMSystem.h"

SMSystem::SMSystem()
{
	
}

SMSystem::SMSystem(unsigned point_count, unsigned spring_count)
{
	mass_point_arr.reserve(point_count);
	spring_arr.reserve(spring_count);
}
//SMSystem::~SMSystem()
//{
//
//}

void SMSystem::Simulate()
{
	CalcSpring();
	AddGlobleForce();
	CalcPoint();
	ClrAllForce();
}

//void SMSystem::MakeTestSurface()
//{
//	for (int i = 0; i < 50; ++i)
//	{
//		mass_point_arr[i] = MassPoint(Vector3f(0, (float)(0.8 - i * 0.02), -1));
//	}
//	for (int i = 0; i < 49; ++i)
//	{
//		Spring s = Spring(mass_point_arr[i], mass_point_arr[i + 1]);
//		memcpy_s(&spring_arr[i], sizeof(Spring), &s, sizeof(Spring));
//		//spring_arr[i] = Spring(mass_point_arr[i], mass_point_arr[i + 1]);
//	}
//}

//Ê¹ÓÃOpenGL»­³öÍ¼Ïñ
void SMSystem::DrawWireframe()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0.2, 0.8);
	glBegin(GL_LINES);
	for (int i = 0; i < spring_arr.size(); ++i)
	{
		glVertex3f(spring_arr[i].point_1.positon[0], spring_arr[i].point_1.positon[1], spring_arr[i].point_1.positon[2]);
		glVertex3f(spring_arr[i].point_2.positon[0], spring_arr[i].point_2.positon[1], spring_arr[i].point_2.positon[2]);
	}
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	for (int i = 0; i < mass_point_arr.size(); ++i)
	{
		glVertex3f(mass_point_arr[i].positon[0], mass_point_arr[i].positon[1], mass_point_arr[i].positon[2]);
	}
	glEnd();
	glFlush();
}

void SMSystem::AddPoint(Vector3f positon, float mass)
{
	mass_point_arr.push_back(MassPoint(positon, mass));
}

void SMSystem::AddPoint(MassPoint point)
{
	mass_point_arr.push_back(point);
}

void SMSystem::AddSpring(int p1_index, int p2_index)
{
	spring_arr.push_back(Spring(mass_point_arr[p1_index], mass_point_arr[p2_index]));
	//memcpy_s(&spring_arr[current_spring_index++], sizeof(Spring), &s, sizeof(Spring));
}

void SMSystem::AddSpring(int p1_index, int p2_index, float length)
{
	spring_arr.push_back(Spring(mass_point_arr[p1_index], mass_point_arr[p2_index], length, 0.2, 0.2));
}

void SMSystem::AddSpring(Spring spring)
{
	spring_arr.push_back(spring);
	//memcpy_s(&spring_arr[current_spring_index++], sizeof(Spring), &spring, sizeof(Spring));
}

void SMSystem::SetPointFixed(int point_index, bool fixed)
{
	mass_point_arr[point_index].fixed = fixed;
}

void SMSystem::CalcPoint()
{
	for (unsigned i = 0; i < mass_point_arr.size(); ++i)
	{
		mass_point_arr[i].Update((float)0.001);
	}
}

void SMSystem::CalcSpring()
{
	for (unsigned i = 0; i < spring_arr.size(); ++i)
	{
		spring_arr[i].CalcAndAppForce();
	}
}

void SMSystem::AddGlobleForce()
{
	for (unsigned i = 0; i < mass_point_arr.size(); ++i)
	{
		mass_point_arr[i].AddForce(gravity * Vector3f(0, -0.1, 0));
	}
	//mass_point_arr[16].AddForce(Vector3f(0, 0.1, 0));
}

void SMSystem::ClrAllForce()
{
	for (unsigned i = 0; i < mass_point_arr.size(); ++i)
	{
		mass_point_arr[i].ClearForce();
	}
}


