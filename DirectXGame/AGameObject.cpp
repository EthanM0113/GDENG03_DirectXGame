#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localRotation = Vector3D::zeros();
	this->localPosition = Vector3D::zeros();
	this->localScale = Vector3D::ones();
	this->localMatrix.setIdentity();
	this->isEnabled = true; // game objects are rendered by default
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
	overrideMatrix = false;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
	overrideMatrix = false;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
	overrideMatrix = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
	overrideMatrix = false;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
	overrideMatrix = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
	overrideMatrix = false;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

void AGameObject::setEnabled(bool flag)
{
	this->isEnabled = flag;
}

bool AGameObject::getEnabled()
{
	return this->isEnabled;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

string AGameObject::getName()
{
	return this->name;
}

Matrix4x4 AGameObject::getLocalMatrix()
{
	return localMatrix;
}

void AGameObject::setLocalMatrix(Matrix4x4 matrix)
{
	localMatrix = matrix;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];
	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];
	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];
	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	this->overrideMatrix = true;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(Vector3D::ones()); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getValues().y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getValues().z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.getMatrixAsArray();
}

void AGameObject::updateLocalMatrix()
{
	//setup transformation matrix for drawing.
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getValues().y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getValues().z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	this->localMatrix = allMatrix;
}

void AGameObject::attachComponent(AComponent* component)
{
	componentList.push_back(component);
	componentTable[component->getName()] = component;
}

void AGameObject::detachComponent(AComponent* component)
{
	// delete from list
	for (int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i]->getName() == component->getName())
		{
			componentList.erase(componentList.begin() + i);
			return;
		}
	}

	// delete from table
	for (auto p : componentTable)
	{
		if (p.second->getName() == component->getName())
		{
			componentTable.erase(p.first);
			return;
		}
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	if (componentTable[name] != nullptr)
		return componentTable[name];

	return nullptr;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, String name)
{
	if (componentTable[name] != nullptr && componentTable[name]->getType() == type)
		return componentTable[name];

	return nullptr;
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList tempList;

	for(int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i]->getType() == type)
			tempList.push_back(componentList[i]);
	}

	return tempList;
}

AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}
