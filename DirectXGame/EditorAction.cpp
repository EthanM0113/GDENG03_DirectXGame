#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	this->owner = gameObject;

	// Immediately get owner's properties
	this->objectName = owner->getName();
	this->localPosition = owner->getLocalPosition();
	this->localScale = owner->getLocalScale();
	this->localRotation = owner->getLocalRotation();
	this->localMatrix = owner->getLocalMatrix();
}

EditorAction::~EditorAction()
{
}

AGameObject* EditorAction::getOwner()
{
	return owner;
}

std::string EditorAction::getOwnerName()
{
	return this->objectName;
}

Vector3D EditorAction::getStorePos()
{
	return this->localPosition;
}

Vector3D EditorAction::getStoredScale()
{
	return this->localScale;
}

Vector3D EditorAction::getStoredRotation()
{
	return this->localRotation;
}

Matrix4x4 EditorAction::getStoredMatrix()
{
	return this->localMatrix;
}
