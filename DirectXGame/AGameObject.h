#pragma once
#include <string>
#include <reactphysics3d/decimal.h>

#include "AComponent.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "BaseComponentSystem.h"

using namespace std;

class VertexShader;
class PixelShader;

class AGameObject
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, AComponent*> ComponentTable;
	typedef std::vector<AComponent*> ComponentList;

	_declspec(align(16)) //make CBData a size of 16-bytes.
		struct CBData {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		float time;
	};

	AGameObject(string name);
	~AGameObject();

	// Abstract Methods
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void setEnabled(bool flag);
	bool getEnabled();

	string getName();

	Matrix4x4 getLocalMatrix();
	void setLocalMatrix(Matrix4x4 matrix);

	void recomputeMatrix(float matrix[16]);
	float* getPhysicsLocalMatrix();

	struct Vertex {
		Vector3D position;
		Vector3D position2;
		Vector3D color;
		Vector3D color2;
	};

	// Component functions
	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	AComponent* findComponentOfType(AComponent::ComponentType type, String name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);

protected:
	string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
	//reactphysics3d::decimal* phyiscsLocalMatrix;
	bool isEnabled;

	// ECS Variables
	ComponentList componentList;
	ComponentTable componentTable;
};