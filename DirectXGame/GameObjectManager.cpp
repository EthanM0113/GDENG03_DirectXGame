#include "GameObjectManager.h"
#include "Cube.h"
#include "GraphicsEngine.h"
#include "ObjectRenderer.h"
#include "PhysicsComponent.h"
#include "PhysicsCube.h"
#include "Plane.h"
#include "TexturedCube.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	delete sharedInstance;
}

void GameObjectManager::applyEditorAction(EditorAction* action)
{

}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	// Chance that object cannot be found
	AGameObject* gameObject = gameObjectMap[name];
	return gameObject;
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return gameObjectList.size();
}

void GameObjectManager::updateAll(float deltaTime)
{
	for(int i = 0; i < gameObjectList.size(); i++)
	{
		if(gameObjectList[i]->getEnabled())
		{
			gameObjectList[i]->update(deltaTime);
			//cout << "My object is updating: " << gameObjectList[i]->getName() << endl;
		}
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for(int i = 0; i < gameObjectList.size(); i++)
	{
		if(gameObjectList[i]->getEnabled())
		{
			gameObjectList[i]->draw(viewportWidth, viewportHeight);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{ 
	gameObjectList.push_back(gameObject); // add game object to list
	gameObjectMap[gameObject->getName()] = gameObject; // add game object to unordered map
}

void GameObjectManager::createObject(PrimitiveType type)
{
	if(type == PrimitiveType::CUBE)
	{
		std::cout << "Cube count " << cubeCount << std::endl;
		// Spawn a Cube at 0,0,0, 1.0 Scale, 0,0,0 Rotation, No Animation
		std::string objName = "Cube";
		if (cubeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(cubeCount));
			objName.append(") ");
		}
		Cube* cubeObject = new Cube(objName);
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(Vector3D(0, 5, 0)); // buggy
		cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
		cubeObject->setObjectType(type);
		GameObjectManager::getInstance()->addObject(cubeObject);

		cubeCount++;
	}
	else if (type == PrimitiveType::PHYSICS_CUBE)
	{
		for(int i = 0 ; i < 20; i++)
		{
			std::string objName = "Physics_Cube";
			if (physicsCubeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(physicsCubeCount));
				objName.append(") ");
			}
			Cube* cubeObject = new Cube(objName);
			cubeObject->setAnimSpeed(0.0f);
			cubeObject->setPosition(Vector3D(0, 5, 0));
			cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
			cubeObject->setObjectType(type);
			GameObjectManager::getInstance()->addObject(cubeObject);
			cubeObject->updateLocalMatrix();

			// Attach Physics Component
			std::string componentName = "PhysicsComponent_";
			componentName.append(objName);
			PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, cubeObject, BodyType::DYNAMIC, 3.0f);
			cubeObject->attachComponent(physicsComponent);

			physicsCubeCount++;
		}
	}
	else if (type == PrimitiveType::TEXTURED_CUBE)
	{
		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		std::string objName = "Textured_Cube";
		if (texturedCubeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(texturedCubeCount));
			objName.append(") ");
		}
		TexturedCube* cubeObject = new TexturedCube(objName, true);
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(Vector3D(0, 5, 0));
		cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
		cubeObject->setObjectType(type);
		GameObjectManager::getInstance()->addObject(cubeObject);

		texturedCubeCount++;
	}
	else if(type == PrimitiveType::PLANE)
	{
		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		std::string objName = "Plane";
		if (planeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(planeCount));
			objName.append(") ");
		}
		Plane* planeObject = new Plane(objName);
		planeObject->setAnimSpeed(0.0f);
		planeObject->setPosition(Vector3D(0, 0, 0));
		planeObject->setRotation(Vector3D(0, 0, 0));
		planeObject->setScale(Vector3D(1, 0.01f, 1));
		planeObject->setObjectType(type);
		GameObjectManager::getInstance()->addObject(planeObject);

		planeCount++;
	}
	else if (type == PrimitiveType::PHYSICS_PLANE)
	{
		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		std::string objName = "Physics_Plane";
		if (physicsPlaneCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(physicsPlaneCount));
			objName.append(") ");
		}
		Plane* planeObject = new Plane(objName);
		planeObject->setAnimSpeed(0.0f);
		planeObject->setPosition(Vector3D(0, 0, 0));
		planeObject->setRotation(Vector3D(0, 0, 0));
		planeObject->setScale(Vector3D(32.f, 0.2f, 32.f));
		planeObject->setObjectType(type);
		GameObjectManager::getInstance()->addObject(planeObject);
		planeObject->updateLocalMatrix();


		// Attach Physics Component
		std::string componentName = "PhysicsComponent_";
		componentName.append(objName);
		PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, planeObject, BodyType::KINEMATIC, 1);
		planeObject->attachComponent(physicsComponent);

		physicsPlaneCount++;
		}
}

void GameObjectManager::createObjectFromFile(std::string objectName, PrimitiveType objectType, Vector3D position,
	Vector3D rotation, Vector3D scale, bool hasRB, float mass, bool isGravity, bool isKinematic)
{
	if (objectType == PrimitiveType::CUBE)
	{
		// Spawn a Cube at 0,0,0, 1.0 Scale, 0,0,0 Rotation, No Animation
		std::string objName = objectName;
		Cube* cubeObject = new Cube(objName);
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(position); // buggy
		cubeObject->setScale(scale);
		cubeObject->setRotation(rotation);
		cubeObject->setObjectType(objectType);
		GameObjectManager::getInstance()->addObject(cubeObject);

		if(hasRB)
		{
			PhysicsComponent* physicsComponent;
			cubeObject->updateLocalMatrix();
			// Attach Physics Component
			std::string componentName = "PhysicsComponent_";
			componentName.append(objName);
			if (isKinematic)
			{
				physicsComponent = new PhysicsComponent(componentName, cubeObject, BodyType::KINEMATIC, mass);
				physicsComponent->setIsStatic(true);
			}
			else
				physicsComponent = new PhysicsComponent(componentName, cubeObject, BodyType::DYNAMIC, mass);

			physicsComponent->setIsGravity(isGravity);
			cubeObject->attachComponent(physicsComponent);
		}
	}
	if (objectType == PrimitiveType::PHYSICS_CUBE)
	{
		std::string objName = objectName;
		Cube* cubeObject = new Cube(objName);
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(position);
		cubeObject->setScale(scale);
		cubeObject->setRotation(rotation);
		cubeObject->setObjectType(objectType);
		GameObjectManager::getInstance()->addObject(cubeObject);
		cubeObject->updateLocalMatrix();

		// Attach Physics Component
		std::string componentName = "PhysicsComponent_";
		componentName.append(objName);
		PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, cubeObject, BodyType::DYNAMIC, mass);
		physicsComponent->setIsGravity(isGravity);
		cubeObject->attachComponent(physicsComponent);
	}
	else if (objectType == PrimitiveType::PLANE)
	{
		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		std::string objName = objectName;
		if (planeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(planeCount));
			objName.append(") ");
		}
		Plane* planeObject = new Plane(objName);
		planeObject->setAnimSpeed(0.0f);
		planeObject->setPosition(position);
		planeObject->setRotation(rotation);
		planeObject->setScale(scale);
		planeObject->setObjectType(objectType);
		GameObjectManager::getInstance()->addObject(planeObject);
	}
	else if (objectType == PrimitiveType::PHYSICS_PLANE)
	{
		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		std::string objName = objectName;
		Plane* planeObject = new Plane(objName);
		planeObject->setAnimSpeed(0.0f);
		planeObject->setPosition(position);
		planeObject->setRotation(rotation);
		planeObject->setScale(scale);
		planeObject->setObjectType(objectType);
		GameObjectManager::getInstance()->addObject(planeObject);
		planeObject->updateLocalMatrix();

		// Attach Physics Component
		std::string componentName = "PhysicsComponent_";
		componentName.append(objName);
		PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, planeObject, BodyType::KINEMATIC, 0.001f);
		planeObject->attachComponent(physicsComponent);
	}
}

void GameObjectManager::createTexturedObjectFromFile(std::string objectName, PrimitiveType objectType,
                                                     Vector3D position, Vector3D rotation, Vector3D scale, std::string materialPath)
{
		if (objectType == PrimitiveType::TEXTURED_CUBE)
		{
			// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
			std::string objName = objectName;
			TexturedCube* cubeObject = new TexturedCube(objName, true);
			cubeObject->setAnimSpeed(0.0f);
			cubeObject->setPosition(position);
			cubeObject->setScale(scale);
			cubeObject->setRotation(rotation);
			cubeObject->setObjectType(objectType);
			cubeObject->getRenderer()->setRenderer(materialPath);
			GameObjectManager::getInstance()->addObject(cubeObject);
	}

}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	PrimitiveType deleteType = gameObject->getObjectType();

	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;


	for (int i = 0; i < gameObjectList.size(); i++) {
		if (this->gameObjectList[i]->getName() == gameObject->getName()) {
			//std::cout << "Object in List: " << gameObjectList[i]->getName() << ", Object: " << gameObject->getName() << std::endl;
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	if (gameObject == gameObjectMap[selectedObjectName])
		gameObjectMap[selectedObjectName] = nullptr;

	delete gameObject;

	// Clear selected object
	selectedObjectName.clear();

	if (deleteType == CUBE)
		cubeCount--;
	else if (deleteType == PHYSICS_CUBE)
		physicsCubeCount--;
	if (deleteType == PLANE)
		planeCount--;
	else if (deleteType == PHYSICS_CUBE)
		physicsPlaneCount--;
}

void GameObjectManager::deleteAllObjects()
{
	while(gameObjectList.size() > 0)
	{
		deleteObject(gameObjectList[0]);
	}
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	selectedObjectName = name;
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if(gameObjectList[i]->getName() == selectedObjectName)
		{
			return gameObjectList[i];
		}
	}

	return nullptr;
}

void GameObjectManager::reattachAllPhysicsComponents()
{
	// Cannot spam makes engine slow
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if(gameObjectList[i]->findComponentOfType(AComponent::Physics) != nullptr)
		{
			PhysicsComponent* physicsComponent = (PhysicsComponent*)gameObjectList[i]->findComponentOfType(AComponent::Physics);
			PhysicsComponent* oldComponent = new PhysicsComponent(physicsComponent->getName(), physicsComponent->getOwner(), physicsComponent->getType(), physicsComponent->getMass());
			oldComponent->setIsActive(physicsComponent->getIsActive());
			oldComponent->setIsStatic(physicsComponent->getIsStatic());
			oldComponent->setIsGravity(physicsComponent->getIsGravity());
			gameObjectList[i]->detachComponent(physicsComponent);

			// Reattach Physics Component
			gameObjectList[i]->attachComponent(oldComponent);
		}
	}
}

int GameObjectManager::getCubeCount()
{
	return cubeCount;
}

int GameObjectManager::getPlaneCount()
{
	return planeCount;
}

int GameObjectManager::getPhysicsCubeCount()
{
	return physicsCubeCount;
}

int GameObjectManager::getPhysicsPlaneCount()
{
	return physicsPlaneCount;
}

int GameObjectManager::getTexturedCubeCount()
{
	return texturedCubeCount;
}

void GameObjectManager::setCubeCount(int count)
{
	this->cubeCount = count;
}

void GameObjectManager::setPlaneCount(int count)
{
	this->planeCount = count;
}

void GameObjectManager::setPhysicsCubeCount(int count)
{
	this->physicsCubeCount = count;
}

void GameObjectManager::setPhysicsPlaneCount(int count)
{
	this->physicsPlaneCount = count;
}

void GameObjectManager::setTexturedCubeCount(int count)
{
	this->texturedCubeCount = count;
}

GameObjectManager::GameObjectManager()
{
	// Set selection to empty
	selectedObjectName.clear();
}

GameObjectManager::~GameObjectManager()
{
}
