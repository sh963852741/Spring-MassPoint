#pragma once
#include <GL/glut.h>
#include <Eigen/Core>
using namespace std;
using namespace Eigen;

enum Side { none = 0x00, left = 0x11, right = 0x12, top = 0x13, bottom = 0x14, front = 0x15, back = 0x16, hit_unknown = 0x10 };
class Sphere
{
public:
	Sphere(Vector3f center = Vector3f(0, 0, -0.6), float radius = 0.2);
	Vector3f center;
	float radius;
	bool Contains(Vector3f position);
	void Draw();
private:

};
class MyRectangle
{
public:
	MyRectangle(Vector3f right_top_near = Vector3f(-0.3, 0.1, -0.4), Vector3f left_bottom_far = Vector3f(-0.5, -0.1, -0.6));
	Vector3f left_bottom_far;
	Vector3f right_top_near;
	void Draw();
	Side Contains(Vector3f position, Vector3f velocity);
private:
};