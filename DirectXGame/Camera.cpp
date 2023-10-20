#include "Camera.h"

#include "EngineTime.h"
#include "InputSystem.h"

Camera::Camera(string name) : AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	// Set World Cam Spawn Translation
	setPosition(0, 0, -2);
	updateViewMatrix();

	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	this->deltaTime = deltaTime;

	Vector3D localPos = getLocalPosition();
	posX = localPos.getValues().x;
	posY = localPos.getValues().y;
	posZ = localPos.getValues().z;
	float moveSpeed = 5.0f;

	// posZ is = m_forward, posX = m_rightward
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "Camera W pressed\n";
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			posX + direction.getValues().x * deltaTime * moveSpeed,
			posY + direction.getValues().y * deltaTime * moveSpeed,
			posZ + direction.getValues().z * deltaTime * moveSpeed);

		setPosition(newPos.getValues().x, newPos.getValues().y, newPos.getValues().z);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		cout << "Camera S pressed\n";
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			posX + direction.getValues().x * deltaTime * -moveSpeed,
			posY + direction.getValues().y * deltaTime * -moveSpeed,
			posZ + direction.getValues().z * deltaTime * -moveSpeed);

		setPosition(newPos.getValues().x, newPos.getValues().y, newPos.getValues().z);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('A'))
	{
		cout << "Camera A pressed\n";
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			posX + direction.getValues().x * deltaTime * -moveSpeed,
			posY + direction.getValues().y * deltaTime * -moveSpeed,
			posZ + direction.getValues().z * deltaTime * -moveSpeed);

		setPosition(newPos.getValues().x, newPos.getValues().y, newPos.getValues().z);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('D'))
	{
		cout << "Camera D pressed\n";
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			posX + direction.getValues().x * deltaTime * moveSpeed,
			posY + direction.getValues().y * deltaTime * moveSpeed,
			posZ + direction.getValues().z * deltaTime * moveSpeed);

		setPosition(newPos.getValues().x, newPos.getValues().y, newPos.getValues().z);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('Q'))
	{
		cout << "Camera Q pressed\n";
		Vector3D direction = Vector3D(0,1,0);
		Vector3D newPos = Vector3D(
			posX + direction.getValues().x * deltaTime * -moveSpeed,
			posY + direction.getValues().y * deltaTime * -moveSpeed,
			posZ + direction.getValues().z * deltaTime * -moveSpeed);

		setPosition(newPos.getValues().x, newPos.getValues().y, newPos.getValues().z);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('E'))
	{
		cout << "Camera E pressed\n";
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			posX + direction.getValues().x * deltaTime * moveSpeed,
			posY + direction.getValues().y * deltaTime * moveSpeed,
			posZ + direction.getValues().z * deltaTime * moveSpeed);

		setPosition(newPos.getValues().x, newPos.getValues().y, newPos.getValues().z);
		updateViewMatrix();
	}

	updateViewMatrix();
}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.getValues().x);
	worldCam = worldCam.multiplyTo(temp);

	temp.setRotationY(localRot.getValues().y);
	worldCam = worldCam.multiplyTo(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	this->localMatrix = worldCam.clone();

	worldCam.inverse();

	this->viewMatrix = worldCam;
}

void Camera::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void Camera::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

Matrix4x4 Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::setSpawnPosition(float x, float y, float z)
{
	setPosition(x, y, z);
	updateViewMatrix();
}

void Camera::onKeyUp(int key)
{
}

void Camera::onKeyDown(int key)
{
}

void Camera::onMouseMove(const Point& deltaPos)
{
	if(isLeftClickHeld)
	{
		float sensitivity = 0.1f;

		Vector3D localRot = this->getLocalRotation();
		rotX = localRot.getValues().x;
		rotY = localRot.getValues().y;
		rotZ = localRot.getValues().z;

		rotX += deltaPos.getY() * deltaTime * sensitivity;
		rotY += deltaPos.getX() * deltaTime * sensitivity;

		setRotation(rotX, rotY, rotZ);
		updateViewMatrix();

	}
}

void Camera::onLeftMouseDown(const Point& deltaPos)
{
	isLeftClickHeld = true;
}

void Camera::onLeftMouseUp(const Point& deltaPos)
{
	isLeftClickHeld = false;
}

void Camera::onRightMouseDown(const Point& deltaPos)
{
}

void Camera::onRightMouseUp(const Point& deltaPos)
{
}
