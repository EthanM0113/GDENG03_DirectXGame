#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "Vector3D.h"


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
class EditorAction;

class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	// Applies EditorAction to respective game object
	void applyEditorAction(EditorAction* action);

	AGameObject* findObjectByName(std::string name);
	List getAllObjects();
	int activeObjects();
	void updateAll(float deltaTime);
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void createObjectFromFile(std::string objectName, PrimitiveType objectType, Vector3D position, Vector3D rotation, Vector3D scale);
	void createTexturedObjectFromFile(std::string objectName, PrimitiveType objectType, Vector3D position, Vector3D rotation, Vector3D scale, std::string materialPath);
	void deleteObject(AGameObject* gameObject);
	void deleteAllObjects();
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();
	void reattachAllPhysicsComponents();

	int getCubeCount();
	int getPlaneCount();
	int getPhysicsCubeCount();
	int getPhysicsPlaneCount();
	int getTexturedCubeCount();

	void setCubeCount(int count);
	void setPlaneCount(int count);
	void setPhysicsCubeCount(int count);
	void setPhysicsPlaneCount(int count);
	void setTexturedCubeCount(int count);

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

