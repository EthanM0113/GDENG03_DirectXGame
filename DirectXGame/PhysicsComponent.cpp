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

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scaleVect.x / 2, scaleVect.y / 2, scaleVect.z / 2));
	rigidBody = physicsWorld->createRigidBody(transform);
	rigidBody->addCollider(boxShape, transform);
	rigidBody->updateMassPropertiesFromColliders();
	rigidBody->setMass(mass);
	rigidBody->setType(type);

	transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
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
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return rigidBody;
}
