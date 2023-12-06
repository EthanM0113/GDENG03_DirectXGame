#pragma once
#include "AGameObject.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

// stores snapshot of user action for undoing and redoing
class EditorAction
{
public:
	EditorAction(AGameObject* gameObject);
	~EditorAction();

	AGameObject* getOwner();
	std::string getOwnerName();
	Vector3D getStorePos();
	Vector3D getStoredScale();
	Vector3D getStoredRotation();
	Matrix4x4 getStoredMatrix();

private:
	AGameObject* owner;
	std::string objectName;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

