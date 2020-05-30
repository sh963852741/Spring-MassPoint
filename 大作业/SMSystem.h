#pragma once
#include <GL/glut.h>
#include "Spring.h"
#include <Eigen/Core>
using namespace Eigen;
class SMSystem
{
public:
	SMSystem();
	~SMSystem();
	void Simulate();
	void MakeTestSurface();
	void DrawWireframe();
private:
	void CalcPoint();
	void CalcSpring();
	void AddGlobleForce();
	MassPoint* mass_point_arr;
	Spring* spring_arr;
};
