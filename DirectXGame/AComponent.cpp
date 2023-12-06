#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, AGameObject* owner)
{
	this->name = name;
	this->type = type;
	this->owner = owner;
}

AComponent::~AComponent()
{
	owner = NULL;
	type = NotSet;
}

void AComponent::attachOwner(AGameObject* owner)
{
	this->owner = owner;
}

void AComponent::detachOwner()
{
	this->owner = nullptr;
}

AGameObject* AComponent::getOwner()
{
	return owner;
}

AComponent::ComponentType AComponent::getType()
{
	return type;
}

AComponent::String AComponent::getName()
{
	return name;
}


void AComponent::perform(float deltaTime)
{
}
