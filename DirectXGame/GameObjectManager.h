#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"

class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType {
		CUBE,
		PHYSICS_CUBE,
		PLANE,
		PHYSICS_PLANE,
		SPHERE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(string name);
	List getAllObjects();
	int activeObjects();
	void updateAll(float deltaTime);
	void renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader, PixelShader* pixelShader);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(string name);
	void setSelectedObject(string name);
	AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;
	List gameObjectList;
	HashTable gameObjectMap;
	string selectedObjectName;
	int cubeCount = 0;
	int planeCount = 0;
	int physicsCubeCount = 0;
	int physicsPlaneCount = 0;
};

