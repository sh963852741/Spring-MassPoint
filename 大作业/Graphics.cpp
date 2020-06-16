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
}

MyRectangle::MyRectangle(Vector3f right_top_near, Vector3f left_bottom_far)
{
	this->right_top_near = right_top_near;
	this->left_bottom_far = left_bottom_far;
}

void MyRectangle::Draw()
{
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(right_top_near[0], right_top_near[1], right_top_near[2]); //”“…œ
	glVertex3f(left_bottom_far[0], right_top_near[1], right_top_near[2]); //◊Û…œ
	glVertex3f(left_bottom_far[0], left_bottom_far[1], right_top_near[2]); //◊Ûœ¬
	glVertex3f(right_top_near[0], left_bottom_far[1], right_top_near[2]); //”“œ¬
	glNormal3f(-1,0,0);
	glVertex3f(left_bottom_far[0], right_top_near[1], right_top_near[2]);
	glVertex3f(left_bottom_far[0], right_top_near[1], left_bottom_far[2]);
	glVertex3f(left_bottom_far[0], left_bottom_far[1], left_bottom_far[2]);
	glVertex3f(left_bottom_far[0], left_bottom_far[1], right_top_near[2]);
	glNormal3f(0, 0, -1);
	glVertex3f(right_top_near[0], right_top_near[1], left_bottom_far[2]);
	glVertex3f(left_bottom_far[0], right_top_near[1], left_bottom_far[2]);
	glVertex3f(left_bottom_far[0], left_bottom_far[1], left_bottom_far[2]);
	glVertex3f(right_top_near[0], left_bottom_far[1], left_bottom_far[2]);
	glNormal3f(1, 0, 0);
	glVertex3f(right_top_near[0], right_top_near[1], right_top_near[2]);
	glVertex3f(right_top_near[0], right_top_near[1], left_bottom_far[2]);
	glVertex3f(right_top_near[0], left_bottom_far[1], left_bottom_far[2]);
	glVertex3f(right_top_near[0], left_bottom_far[1], right_top_near[2]);
	glNormal3f(0, 1, 0);
	glVertex3f(left_bottom_far[0], right_top_near[1], right_top_near[2]);
	glVertex3f(right_top_near[0], right_top_near[1], right_top_near[2]);
	glVertex3f(right_top_near[0], right_top_near[1], left_bottom_far[2]);
	glVertex3f(left_bottom_far[0], right_top_near[1], left_bottom_far[2]);
	glNormal3f(0, -1, 0);
	glVertex3f(left_bottom_far[0], left_bottom_far[1], right_top_near[2]);
	glVertex3f(right_top_near[0], left_bottom_far[1], right_top_near[2]);
	glVertex3f(right_top_near[0], left_bottom_far[1], left_bottom_far[2]);
	glVertex3f(left_bottom_far[0], left_bottom_far[1], left_bottom_far[2]);
	glEnd();
}

Side MyRectangle::Contains(Vector3f position, Vector3f velocity)
{
	if (position[0]< right_top_near[0] && position[1] < right_top_near[1] && position[2] < right_top_near[2]
		&& position[0] > left_bottom_far[0] && position[1] > left_bottom_far[1] && position[2] > left_bottom_far[2])
	{
		float res_t = 0;
		//∑®œÚ¡ø
		Vector3f n;
		//ºÏ≤‚top
		n = Vector3f(0, -1, 0);
		res_t = n.dot(right_top_near - position) / n.dot(velocity);
		if (res_t < 0)return Side::top;
		//ºÏ≤‚right
		n = Vector3f(-1, 0, 0);
		res_t = n.dot(right_top_near - position) / n.dot(velocity);
		if (res_t < 0)return Side::right;
		//ºÏ≤‚front
		n = Vector3f(0, 0, -1);
		res_t = n.dot(right_top_near - position) / n.dot(velocity);
		if (res_t < 0)return Side::front;
		//ºÏ≤‚back
		n = Vector3f(0, 0, 1);
		res_t = n.dot(left_bottom_far - position) / n.dot(velocity);
		if (res_t < 0)return Side::back;
		//ºÏ≤‚left
		n = Vector3f(1, 0, 0);
		res_t = n.dot(left_bottom_far - position) / n.dot(velocity);
		if (res_t < 0)return Side::left;
		//ºÏ≤‚bottom
		n = Vector3f(0, 1, 0);
		res_t = n.dot(left_bottom_far - position) / n.dot(velocity);
		if (res_t < 0)return Side::bottom;
		throw hit_unknown;
		return Side::hit_unknown;
	}
	return none;
}
