#pragma once
#include <GL/glut.h>
#include <Eigen/Core>
using namespace std;
using namespace Eigen;
class Sphere
{
public:
	Sphere(Vector3f center = Vector3f(0, 0, -0.4), float radius = 0.2);
	Vector3f center;
	float radius;
	bool Contains(Vector3f position);
	void Draw();
private:

};