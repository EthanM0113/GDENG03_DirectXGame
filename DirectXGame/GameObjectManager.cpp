#include "GameObjectManager.h"
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

AGameObject* GameObjectManager::findObjectByName(string name)
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
		gameObjectList[i]->update(deltaTime);
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader,
	PixelShader* pixelShader)
{
	for(int i = 0; i < gameObjectList.size(); i++)
	{
		gameObjectList[i]->draw(viewportWidth, viewportHeight, vertexShader, pixelShader);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{ 
	gameObjectList.push_back(gameObject); // add game object to list
	gameObjectMap[gameObject->getName()] = gameObject; // add game object to unordered map
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
}

void GameObjectManager::deleteObjectByName(string name)
{
}

void GameObjectManager::setSelectedObject(string name)
{
	selectedObjectName = name;
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

	cout << "No object selected";
	return nullptr;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}
