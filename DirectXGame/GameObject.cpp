#include "GameObject.h"

void GameObject::SetOrigin(Vector3D originalPos)
{
	// Set Origin of Game Object
	origin = originalPos;
}


void GameObject::SetScale(Vector3D newScale)
{
	// Set Scale of Game Object
	scale = newScale;
}

