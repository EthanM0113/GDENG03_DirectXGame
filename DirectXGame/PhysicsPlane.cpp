#include "PhysicsPlane.h"
#include "GraphicsEngine.h"
#include "SceneCameraHandler.h"
#include "SwapChain.h"

PhysicsPlane::PhysicsPlane(string name, void* shaderByteCode, size_t sizeShader) :AGameObject(name)
{
	//create buffers for drawing. vertex data that needs to be drawn are temporarily placed here.
	//White Quad
	Vertex quadList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-1.0f,-1.0f,-1.0f),    Vector3D(1,1,1),  Vector3D(0.2f,0,0) },
		{Vector3D(-1.0f,1.0f,-1.0f),    Vector3D(1,1,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(1.0f,1.0f,-1.0f),   Vector3D(1,1,1),  Vector3D(0.2f,0.2f,0) },
		{Vector3D(1.0f,-1.0f,-1.0f),     Vector3D(1,1,1), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(1.0f,-1.0f,1.0f),    Vector3D(1,1,1), Vector3D(0,0.2f,0) },
		{Vector3D(1.0f,1.0f,1.0f),    Vector3D(1,1,1), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-1.0f,1.0f,1.0f),   Vector3D(1,1,1),  Vector3D(0,0.2f,0.2f) },
		{Vector3D(-1.0f,-1.0f,1.0f),     Vector3D(1,1,1), Vector3D(0,0.2f,0) },
	};

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	//create constant buffer
	cbData = {};
	cbData.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));
}

PhysicsPlane::~PhysicsPlane()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	AGameObject::~AGameObject();
}

void PhysicsPlane::update(float deltaTime)
{

	if (speed > 0.0f)
	{
		this->ticks += deltaTime;
		float rotSpeed = this->ticks * this->speed;
		this->setRotation(rotSpeed, rotSpeed, rotSpeed);


		if (this->speed <= 1.0f) {
			this->ticks += deltaTime;

			float rotSpeed = this->ticks * this->speed;
			this->setRotation(rotSpeed, rotSpeed, rotSpeed);
		}
		else if (this->speed >= 10.0f) {
			this->ticks -= deltaTime;

			float rotSpeed = this->ticks * this->speed;
			this->setRotation(rotSpeed, rotSpeed, rotSpeed);
		}
	}
}

void PhysicsPlane::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	cbData = {};
	//cbData.time = this->ticks * this->speed;
	// Test Case 4
	cbData.time = this->ticks * 0.07f;

	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}

	Matrix4x4 allMatrix;
	allMatrix.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	//cout << "Cube Pos " << localPosition.getValues().x << localPosition.getValues().y << localPosition.getValues().z << endl;

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(this->getLocalScale());

	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setRotationZ(rotation.getValues().z);
	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setRotationX(rotation.getValues().x);
	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setRotationY(rotation.getValues().y);

	// Combine x-y-z rotation matrices into one.
	Matrix4x4 rotMatrix;
	rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	//Scale --> Rotate --> Translate as recommended order.
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	cbData.worldMatrix = allMatrix;

	// from world space to view space of camera
	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.viewMatrix = cameraMatrix;
	//cbData.viewMatrix.setIdentity();

	cbData.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	// set shaders
	deviceContext->setVertexShader(vertexShader);
	deviceContext->setPixelShader(pixelShader);

	this->constantBuffer->update(deviceContext, &cbData);
	deviceContext->setConstantBuffer(vertexShader, this->constantBuffer);
	deviceContext->setConstantBuffer(pixelShader, this->constantBuffer);

	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void PhysicsPlane::setAnimSpeed(float speed)
{
	this->speed = speed;
}
