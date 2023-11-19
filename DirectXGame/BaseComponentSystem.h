#pragma once
#include <string>

#include "PhysicsSystem.h"

class BaseComponentSystem
{
public:
	typedef std::string String;

	static BaseComponentSystem* getInstance();
	static void initialize();
	static void destroy();

	PhysicsSystem* getPhysicsSystem();

protected:
	BaseComponentSystem();
	~BaseComponentSystem();

private:
	BaseComponentSystem(BaseComponentSystem const&) {};
	BaseComponentSystem& operator=(BaseComponentSystem const&) {};
	static BaseComponentSystem* sharedInstance;
	PhysicsSystem* physicsSystem;
};

