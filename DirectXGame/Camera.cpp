#include "Camera.h"

#include "EngineTime.h"
#include "InputSystem.h"

Camera::Camera(string name) : AGameObject(name)
{
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
	float moveSpeed = 10.0f;

	// posZ is = m_forward, posX = m_rightward
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "Camera W pressed\n";
		posZ += deltaTime * moveSpeed;
		setPosition(posX, posY, posZ);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		cout << "Camera S pressed\n";
		posZ -= deltaTime * moveSpeed;
		setPosition(posX, posY, posZ);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('A'))
	{
		cout << "Camera A pressed\n";
		posX -= deltaTime * moveSpeed;
		setPosition(posX, posY, posZ);
		updateViewMatrix();
	}
	if (InputSystem::getInstance()->isKeyDown('D'))
	{
		cout << "Camera D pressed\n";
		posX += deltaTime * moveSpeed;
		setPosition(posX, posY, posZ);
		updateViewMatrix();
	}

	updateViewMatrix();
}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void Camera::updateViewMatrix()
{
	worldCam.setIdentity();

	Vector3D localRot = this->getLocalRotation();
	rotX = localRot.getValues().x;
	rotY = localRot.getValues().y;
	rotZ = localRot.getValues().z;

	Matrix4x4 temp;
	temp.setIdentity();
	temp.setRotationX(rotX);
	worldCam = worldCam.multiplyTo(temp);

	temp.setIdentity();
	temp.setRotationY(rotY);
	worldCam = worldCam.multiplyTo(temp);

	Vector3D new_pos = worldCam.getTranslation() + worldCam.getZDirection() * (posZ * 0.1f);

	new_pos = new_pos + worldCam.getXDirection() * (posX * 0.1f);

	temp.setIdentity();
	temp.setTranslation(new_pos);
	worldCam = worldCam.multiplyTo(temp);

	worldCam.inverse();
	this->localMatrix = worldCam;
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
	return localMatrix;
}

void Camera::onKeyUp(int key)
{
	// z is = m_forward, x = m_rightward
	posX = 0;
	posZ = 0;
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
