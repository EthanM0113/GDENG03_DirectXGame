#include "AGameObject.h"

void AGameObject::SetOrigin(Vector3D originalPos)
{
	// Set Origin of Game Object
	origin = originalPos;
}


void AGameObject::SetScale(Vector3D newScale)
{
	// Set Scale of Game Object
	scale = newScale;
}

