#include "PhysicsSystem.h"

#include "BaseComponentSystem.h"
#include "EngineTime.h"
#include "PhysicsComponent.h"

//using namespace std;

PhysicsSystem::PhysicsSystem()
{
	// Create physics engine and world
	physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	physicsWorld = physicsCommon->createPhysicsWorld(settings);

	std::cout << "Physics System Initialized" << std::endl;
}

PhysicsSystem::~PhysicsSystem()
{
	delete physicsCommon;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	componentList.push_back(component); // list registry
	componentTable[component->getName()] = component; // table registry
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	// delete from list
	for(int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i]->getName() == component->getName())
			componentList.erase(componentList.begin() + i);
	}

	// delete from table
	for (auto p : componentTable)
	{
		if(p.second->getName() == component->getName())
		{
			componentTable.erase(p.first);
			return;
		}
	}
}

void PhysicsSystem::unregisterComponentByName(String name)
{
	if (componentTable[name] != nullptr)
		componentTable.erase(name);
}

PhysicsComponent* PhysicsSystem::findComponentByName(String name)
{
	if (componentTable[name] != nullptr)
		return componentTable[name];

	return nullptr;
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return componentList;
}

void PhysicsSystem::updateAllComponents(float deltaTime)
{
	if(deltaTime > 0.0f)
	{
		physicsWorld->update(deltaTime);
		for (int i = 0; i < componentList.size(); i++)
		{
			componentList[i]->perform(deltaTime);
		}
	}
}

void PhysicsSystem::setSleepOfAllComponents(bool flag)
{
	for (int i = 0; i < componentList.size(); i++)
	{
		componentList[i]->getRigidBody()->setIsSleeping(flag);
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return physicsCommon;
}
