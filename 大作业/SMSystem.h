#pragma once
#include <GL/glut.h>
#include "Spring.h"
#include <Eigen/Core>
#include <vector>
using namespace std;
using namespace Eigen;
class SMSystem
{
public:
	SMSystem();
	SMSystem(unsigned point_count, unsigned spring_count);
	//~SMSystem();
	void Simulate();
	//void MakeTestSurface();
	void DrawWireframe();
	void AddPoint(Vector3f positon, float mass = 1.0);
	void AddPoint(MassPoint point);
	void AddSpring(int p1_index, int p2_index);
	void AddSpring(Spring spring);
private:
	//int current_point_index = 0;
	//int current_spring_index = 0;
	void CalcPoint();
	void CalcSpring();
	void AddGlobleForce();
	vector<MassPoint> mass_point_arr;
	vector<Spring> spring_arr;
};
