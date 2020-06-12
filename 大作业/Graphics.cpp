#include "Graphics.h"

Sphere::Sphere(Vector3f center, float radius)
{
	this->center = center;
	this->radius = radius;
}

bool Sphere::Contains(Vector3f position)
{
	float distance = (center - position).norm();
	return radius > distance;
}

void Sphere::Draw()
{
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(radius, 40, 50);
	glPopMatrix();
	glFlush();
}
