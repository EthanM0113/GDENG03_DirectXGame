#include "GameObjectManager.h"
#include "Cube.h"
#include "GraphicsEngine.h"
#include "Plane.h"

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
		if(gameObjectList[i]->getEnabled())
		{
			gameObjectList[i]->update(deltaTime);
		}
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader,
	PixelShader* pixelShader)
{
	for(int i = 0; i < gameObjectList.size(); i++)
	{
		if(gameObjectList[i]->getEnabled())
		{
			gameObjectList[i]->draw(viewportWidth, viewportHeight, vertexShader, pixelShader);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{ 
	gameObjectList.push_back(gameObject); // add game object to list
	gameObjectMap[gameObject->getName()] = gameObject; // add game object to unordered map
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	if(type == PrimitiveType::CUBE)
	{
		GraphicsEngine* graphEngine = GraphicsEngine::get();

		VertexShader* m_vertex_shader;
		PixelShader* m_pixel_shader;

		//compile basic vertex shader
		graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
		m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

		// Spawn a Cube at 0,0,0, 1.0 Scale, 0,0,0 Rotation, No Animation
		string objName = "Cube";
		if (cubeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(cubeCount));
			objName.append(") ");
		}
		Cube* cubeObject = new Cube(objName, shaderByteCode, sizeShader);
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(Vector3D(0, 0, 0));
		cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
		GameObjectManager::getInstance()->addObject(cubeObject);

		shaderByteCode = nullptr;
		sizeShader = 0;
		GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
		m_vertex_shader = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

		graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

		//compile basic pixel shader
		graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
		m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
		graphEngine->releaseCompiledShader();

		cubeCount++;
	}
	else if(type == PrimitiveType::PLANE)
	{
		GraphicsEngine* graphEngine = GraphicsEngine::get();

		VertexShader* m_vertex_shader;
		PixelShader* m_pixel_shader;

		//compile basic vertex shader
		graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
		m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		string objName = "Plane";
		if (planeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(planeCount));
			objName.append(") ");
		}
		Plane* planeObject = new Plane(objName, shaderByteCode, sizeShader);
		planeObject->setAnimSpeed(0.0f);
		planeObject->setPosition(Vector3D(0, 0, 0));
		planeObject->setRotation(Vector3D(7.85, 0, 0));
		planeObject->setScale(Vector3D(3.0, 3.0, 3.0));
		GameObjectManager::getInstance()->addObject(planeObject);

		shaderByteCode = nullptr;
		sizeShader = 0;
		GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
		m_vertex_shader = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

		graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

		//compile basic pixel shader
		graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
		m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
		graphEngine->releaseCompiledShader();

		planeCount++;
	}
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
	// Set selection to empty
	selectedObjectName.clear();
}

GameObjectManager::~GameObjectManager()
{
}
