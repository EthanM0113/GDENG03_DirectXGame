#include "AppWindow.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Cube.h"
#include "Vector3D.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "MathUtils.h"
#include "Matrix4x4.h"
#include "AGameObject.h"
#include "SceneCameraHandler.h"


void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	EngineTime::initialize();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);
	SceneCameraHandler::initialize();

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = getClientWindowRect();

	m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();
	m_index_buffer = GraphicsEngine::get()->createIndexBuffer();

	std::cout << "hwnd: " << this->m_hwnd;
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	//compile basic vertex shader
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	// Get the system time.
	unsigned seed = time(0);

	// Seed the random number generator.
	srand(seed);


	/* Multiple Cubes Instantiation
	for (int i = 0; i < 10; i++) {
		float x = MathUtils::randomFloat(-0.75, 0.75f);
		float y = MathUtils::randomFloat(-0.75, 0.75f);
		float z = MathUtils::randomFloat(-0.75, 0.75f);

		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		//cubeObject->setAnimSpeed(MathUtils::randomFloat(-3.75f, 3.75f));
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
		this->cubeList.push_back(cubeObject);
	}
	*/

	/*
	for (int i = 0; i < 1; i++) {
		float x = 0;
		float y = 0;
		float z = 0;

		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		//cubeObject->setAnimSpeed(MathUtils::randomFloat(-3.75f, 3.75f));
		cubeObject->setAnimSpeed(1.0f);
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(1, 1, 1));
		this->cubeList.push_back(cubeObject);
	}
	*/

	// Test Case 6 + 7
	for (int i = 0; i < 3; i++) {
		float x = 0;
		float y = 0;
		float z = 0;
		if(i == 0)
		{
			x = -1.5f;
			y = 1.0f;
			z = -3.0f;
		}
		if (i == 1)
		{
			x = 0.0f;
			y = 1.0f;
			z = 0.0f;
		}
		if (i == 2)
		{
			x = 2.6f;
			y = 1.0f;
			z = 2.0f;
		}

		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		//cubeObject->setAnimSpeed(MathUtils::randomFloat(-3.75f, 3.75f));
		cubeObject->setAnimSpeed(0.0f);
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(0.5f, 0.5f, 0.5f));
		this->cubeList.push_back(cubeObject);
	}

	// Make Plane (Cube w/ 0 Y Scale)
	Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
	cubeObject->setAnimSpeed(0.0f);
	cubeObject->setPosition(Vector3D(0, -1, 0));
	cubeObject->setScale(Vector3D(7, 0, 7));
	this->cubeList.push_back(cubeObject);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vertex_shader = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

	//compile basic pixel shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
	graphEngine->releaseCompiledShader();
}

void AppWindow::updateCamera()
{
	cc.time = ::GetTickCount();

	m_delta_pos += EngineTime::getDeltaTime() / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	m_delta_scale += EngineTime::getDeltaTime() / 0.55f;

	cc.worldMatrix.setIdentity();

	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cout << "Cam X Rotation: " << m_rot_x << endl;
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cout << "Cam Y Rotation: " << m_rot_y << endl;
	world_cam *= temp;


	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	temp.setIdentity();
	temp.setTranslation(new_pos);
	world_cam *= temp; 

	m_world_cam = world_cam;


	world_cam.inverse();

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
}

void AppWindow::onUpdate()
{
	InputSystem::getInstance()->update();

	ticks += EngineTime::getDeltaTime() * 1.0f;

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0.16, 0.16, 0.16, 1);

	RECT rc = getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	//updateCamera();
	SceneCameraHandler::getInstance()->update(EngineTime::getDeltaTime());

	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->update(EngineTime::getDeltaTime());
		cubeList[i]->draw(width, height, m_vertex_shader, m_pixel_shader);
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vertex_buffer->release();
	m_index_buffer->release();
	m_constant_buffer->release();

	m_vertex_shader->release();
	m_pixel_shader->release();

	InputSystem::destroy();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
	SceneCameraHandler::getInstance()->onFocus();
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
	SceneCameraHandler::getInstance()->onKillFocus();
}


void AppWindow::onKeyDown(int key)
{
	/*
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		for (int i = 0; i < cubeList.size(); i++) {
			cubeList[i]->setAnimSpeed(3.75f);
		}
	}
	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		for (int i = 0; i < cubeList.size(); i++) {
			cubeList[i]->setAnimSpeed(-3.75f);
		}
	}
	*/
}

void AppWindow::onKeyUp(int key)
{
	/*
	if (InputSystem::getInstance()->isKeyUp('W') || InputSystem::getInstance()->isKeyUp('S'))
	{
		for (int i = 0; i < cubeList.size(); i++) {
			cubeList[i]->setAnimSpeed(0.0f);
		}
	}
	*/
}

void AppWindow::onMouseMove(const Point& deltaPos)
{
}

void AppWindow::onLeftMouseDown(const Point& deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point& deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point& deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point& deltaPos)
{
}



AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}