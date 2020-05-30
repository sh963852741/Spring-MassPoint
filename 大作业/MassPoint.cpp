#include "MassPoint.h"

MassPoint::MassPoint(Vector3f positon, float mass, Vector3f velocity)
{
	this->positon = positon;
	this->mass = mass;
	this->velocity = velocity;
	force = Vector3f(0, 0, 0);
}

void MassPoint::AddForce(Vector3f force)
{
	this->force += force;
}

void MassPoint::Update(float timespan)
{
	velocity += (force / mass) * timespan;
	positon += velocity * timespan;
}
