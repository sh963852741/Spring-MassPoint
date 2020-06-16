#pragma once
#include <GL/glut.h>
#include "Spring.h"
#include "Graphics.h"
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
	void DrawGraphyics();
	void AddPoint(Vector3f positon, float mass = 1.0);
	void AddPoint(MassPoint point);
	void AddSpring(int p1_index, int p2_index);
	void AddSpring(int p1_index, int p2_index,float length);
	void AddSpring(Spring spring);
	void SetPointFixed(int point_index, bool fixed = true);
private:
	//int current_point_index = 0;
	//int current_spring_index = 0;
	float gravity = 9.8 * 0.0001;
	void CalcPoint();
	void CalcSpring();
	void AddGlobleForce();
	void ClrAllForce();
	vector<MassPoint> mass_point_arr;
	vector<Spring> spring_arr;
	Sphere ball;
	MyRectangle cube;
};
