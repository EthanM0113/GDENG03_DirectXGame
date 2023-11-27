#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(String name, bool skipInit) : Cube(name, skipInit)
{
}

PhysicsCube::~PhysicsCube()
{
	// Detach physics component
	this->detachComponent(this->findComponentOfType(AComponent::Physics));
	Cube::~Cube();
}

void PhysicsCube::update(float deltaTime)
{
	Cube::update(deltaTime);
}

void PhysicsCube::draw(int width, int height)
{
	Cube::draw(width, height);
}