#include "GameObjectManager.h"
#include "Cube.h"
#include "GraphicsEngine.h"
#include "PhysicsComponent.h"
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
			//cout << "My object is updating: " << gameObjectList[i]->getName() << endl;
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
			//cout << "Position: " << gameObjectList[i]->getLocalPosition().getValues().x << " " << gameObjectList[i]->getLocalPosition().getValues().y << " " <<gameObjectList[i]->getLocalPosition().getValues().z << endl;
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
	else if (type == PrimitiveType::PHYSICS_CUBE)
	{
		for(int i = 0 ; i < 20; i++)
		{
			GraphicsEngine* graphEngine = GraphicsEngine::get();

			VertexShader* m_vertex_shader;
			PixelShader* m_pixel_shader;

			//compile basic vertex shader
			graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
			m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

			string objName = "Physics_Cube";
			if (physicsCubeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(physicsCubeCount));
				objName.append(") ");
			}
			Cube* cubeObject = new Cube(objName, shaderByteCode, sizeShader);
			cubeObject->setAnimSpeed(0.0f);
			cubeObject->setPosition(Vector3D(0, 3, 0));
			cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
			GameObjectManager::getInstance()->addObject(cubeObject);

			// Attach Physics Component
			string componentName = "PhysicsComponent_";
			componentName.append(objName);
			PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, cubeObject, BodyType::DYNAMIC, 1000.0f);
			cubeObject->attachComponent(physicsComponent);

			shaderByteCode = nullptr;
			sizeShader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
			m_vertex_shader = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

			graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

			//compile basic pixel shader
			graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
			m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
			graphEngine->releaseCompiledShader();

			physicsCubeCount++;
		}
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
		planeObject->setScale(Vector3D(3.0, 3.0f, 1.0f));
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
	else if (type == PrimitiveType::PHYSICS_PLANE)
	{
		GraphicsEngine* graphEngine = GraphicsEngine::get();

		VertexShader* m_vertex_shader;
		PixelShader* m_pixel_shader;

		//compile basic vertex shader
		graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
		m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

		// Spawn a Plane at 0,0,0, 1.0 Scale, 7.85,0,0 Rotation, No Animation
		string objName = "Physics_Plane";
		if (physicsPlaneCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(physicsPlaneCount));
			objName.append(") ");
		}
		Plane* planeObject = new Plane(objName, shaderByteCode, sizeShader);
		planeObject->setAnimSpeed(0.0f);
		planeObject->setPosition(Vector3D(0, 0, 0));
		planeObject->setRotation(Vector3D(7.85, 0, 0));
		planeObject->setScale(Vector3D(13.0f, 13.0f, 1.0f));
		GameObjectManager::getInstance()->addObject(planeObject);

		// Attach Physics Component
		string componentName = "PhysicsComponent_";
		componentName.append(objName);
		PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, planeObject, BodyType::STATIC, 0.001f);
		planeObject->attachComponent(physicsComponent);

		shaderByteCode = nullptr;
		sizeShader = 0;
		GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
		m_vertex_shader = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);

		graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

		//compile basic pixel shader
		graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
		m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
		graphEngine->releaseCompiledShader();

		physicsPlaneCount++;
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
