#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(String name, AGameObject* owner, BodyType type, float mass);
	~PhysicsComponent();
	void perform(float deltaTime) override;
	RigidBody* getRigidBody();

	void setIsActive(bool flag);
	bool getIsActive();

	void setIsStatic(bool flag);
	bool getIsStatic();

	void setIsGravity(bool flag);
	bool getIsGravity();

	void setMass(float newMass);
	float getMass();

	void SetType(BodyType type);
	BodyType getType();

	void applyForce(Vector3 forceVector);

private:
	RigidBody* rigidBody;
};



