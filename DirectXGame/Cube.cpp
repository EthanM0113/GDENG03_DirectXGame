#include "Cube.h"
#include "GraphicsEngine.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"
#include "SwapChain.h"

Cube::Cube(std::string name, bool skipInit) :AGameObject(name)
{
	if (skipInit)
		return;

	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	//create buffers for drawing. vertex data that needs to be drawn are temporarily placed here.
	Vertex quadList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) },
	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

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

	//create constant buffer
	CBData cbData = {};
	cbData.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));
}

Cube::~Cube()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;

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

	/*Test Case 3
	this->ticks += deltaTime;

	m_time += 1.57f * deltaTime;
	float lerpSpeed = (sin(m_time) + 1.0f) / 2.0f;
	// Lerp Scale
	Vector3D oldScale = { 1.0f, 1.0f, 1.0f };
	Vector3D newScale = { 0.25, 0.25, 0.25 };
	Vector3D lerpScale = lerpScale.lerp(oldScale, newScale, lerpSpeed);
	setScale(lerpScale.getValues().x, lerpScale.getValues().y, lerpScale.getValues().z);

	// Lerp Position (Move in X and Y axis, move diagonally)
	Vector3D oldPos = { 0.0f, 0.0f, 0.0f };
	Vector3D newPos = { 1.0f, 1.0f, 0.0f};
	Vector3D lerpPos = lerpPos.lerp(oldPos, newPos, lerpSpeed);
	setPosition(lerpPos.getValues().x, lerpPos.getValues().y, lerpPos.getValues().z);
	*/
	/*Test Case 4
	this->ticks += deltaTime;

	m_time += 1.57f * deltaTime;
	float lerpSpeed = (sin(m_time) + 1.0f) / 2.0f;
	// Lerp Scale
	Vector3D newScale = { 1.0f, 0.0f, 1.0f };
	Vector3D lerpScale = lerpScale.lerp(oldScale, newScale, 0.57f * deltaTime);
	oldScale = lerpScale;
	cout << "LerpScale, X: " << lerpScale.getValues().x << ", Y: " << lerpScale.getValues().y << ", Z: " << lerpScale.getValues().z << endl;
	setScale(lerpScale.getValues().x, lerpScale.getValues().y, lerpScale.getValues().z);
	*/
	
}

void Cube::draw(int width, int height)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	//set vertex shader and pixel shader for the object
	ShaderNames shaderNames;
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));


	CBData cbData = {};

	if (this->overrideMatrix)
	{
		cbData.worldMatrix = this->localMatrix;
	}
	else
	{
		this->updateLocalMatrix();
		cbData.worldMatrix = this->localMatrix;
	}

	cbData.viewMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();

	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	cbData.projMatrix.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	this->constantBuffer->update(deviceContext, &cbData);
	deviceContext->setConstantBuffer(this->constantBuffer);

	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
	
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
