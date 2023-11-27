#pragma once
#include <string>
#include <unordered_map>
#include <vector>

enum PrimitiveType {
	NONE,
	TEXTURED_CUBE,
	CUBE,
	PHYSICS_CUBE,
	PLANE,
	PHYSICS_PLANE,
	SPHERE
};

class AGameObject;
class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	List getAllObjects();
	int activeObjects();
	void updateAll(float deltaTime);
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;
	List gameObjectList;
	HashTable gameObjectMap;
	std::string selectedObjectName;
	AGameObject* selectedObject;
	int cubeCount = 0;
	int planeCount = 0;
	int physicsCubeCount = 0;
	int physicsPlaneCount = 0;
	int texturedCubeCount = 0;
};

