#pragma once
#include <Eigen/Core>
using namespace std;
using namespace Eigen;
class MassPoint
{
public:
	bool fixed = false;
	MassPoint(Vector3f positon, float mass = 1.0, Vector3f velocity = Vector3f(0, 0, 0));
	float mass;
	Vector3f positon;
	Vector3f velocity;
	void AddForce(Vector3f force);
	void Update(float timespan);
	void ClearForce();
private:
	Vector3f force;
};