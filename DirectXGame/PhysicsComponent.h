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

private:
	RigidBody* rigidBody;
};

