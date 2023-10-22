#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera: public AGameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void updateViewMatrix();
	void onFocus();
	void onKillFocus();
	void setGUIHoverFlag(bool guiHoverFlag);
	Matrix4x4 getViewMatrix();
	void setSpawnPosition(float x, float y, float z);

	virtual void onKeyUp(int key) override;
	virtual void onKeyDown(int key) override;
	virtual void onMouseMove(const Point& deltaPos) override;
	virtual void onLeftMouseDown(const Point& deltaPos) override;
	virtual void onLeftMouseUp(const Point& deltaPos) override;
	virtual void onRightMouseDown(const Point& deltaPos) override;
	virtual void onRightMouseUp(const Point& deltaPos) override;

private:
	Matrix4x4 worldCam;
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	float deltaTime;
	bool isLeftClickHeld = false;
	bool isImGUIWindowHovered = false;
	Vector3D forwardDirection;
	Vector3D backwardDirection;
	Matrix4x4 viewMatrix;
};

