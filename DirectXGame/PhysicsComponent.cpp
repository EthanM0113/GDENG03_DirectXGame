#include "PhysicsComponent.h"

#include "AComponent.h"
#include "AGameObject.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner, BodyType type, float mass) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	// register new physics components to physics system
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// create rigidbody in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Vector3D::Vect scaleVect = scale.getValues();
	Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

	if(type == BodyType::DYNAMIC) 	// Game Objects
	{
		BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scaleVect.x / 2, scaleVect.y / 2, scaleVect.z / 2));
		rigidBody = physicsWorld->createRigidBody(transform);
		rigidBody->addCollider(boxShape, transform);
		rigidBody->updateMassPropertiesFromColliders();
		rigidBody->setMass(mass);
		rigidBody->setType(type);
		rigidBody->setLocalCenterOfMass(Vector3(0, 0, 0));
		//rigidBody->setIsSleeping(true);

		transform = rigidBody->getTransform();
		float matrix[16];
		transform.getOpenGLMatrix(matrix);

		this->getOwner()->recomputeMatrix(matrix);
	}
	else if(type == BodyType::STATIC) // Plane Floor
	{
		BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scaleVect.x, scaleVect.z * 2.78, scaleVect.y)); // z and y should be swapped for some reason
		rigidBody = physicsWorld->createRigidBody(transform);
		rigidBody->addCollider(boxShape, transform);
		rigidBody->updateMassPropertiesFromColliders();
		rigidBody->setMass(mass);
		rigidBody->setType(type);
		rigidBody->setLocalCenterOfMass(Vector3(0, 0, 0));

		transform = rigidBody->getTransform();
		float matrix[16];
		transform.getOpenGLMatrix(matrix);

		this->getOwner()->recomputeMatrix(matrix);
	}

}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	getOwner()->recomputeMatrix(matrix);

	if(rigidBody->getType() != BodyType::STATIC)
	{
		getOwner()->setRotation(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z);
		getOwner()->setPosition(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);
	}

	//cout << "My component is updating: " << name << " owned by " << owner->getName() << endl;
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return rigidBody;
}
