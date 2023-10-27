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
#include "UIManager.h"
#include "GameObjectManager.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	EngineTime::initialize();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);
	SceneCameraHandler::initialize();
	UIManager::initialize(m_hwnd);
	GameObjectManager::getInstance()->initialize();

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


	// Multiple Cubes Instantiation, for now turn this off
	/*
	for (int i = 0; i < 50; i++) {
		float x = MathUtils::randomFloat(-1.0f, 1.0f);
		float y = MathUtils::randomFloat(-1.0f, 1.0f);
		float z = MathUtils::randomFloat(-1.0f, 1.0f);

		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		//cubeObject->setAnimSpeed(MathUtils::randomFloat(-3.75f, 3.75f));
		cubeObject->setAnimSpeed(1.0);
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
		this->cubeList.push_back(cubeObject);
		GameObjectManager::getInstance()->addObject(cubeObject);
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

	shader_byte_code = nullptr;
	size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vertex_shader = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

	//compile basic pixel shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
	graphEngine->releaseCompiledShader();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());
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
	/* Popup Demo Window
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow(); // Show demo window! :)
	*/
	/*
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// Simple GUI Window HO
	ImGui::SetNextWindowSize(ImVec2(500, 150));
	ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoResize);                
	{
		ImGui::Text("Below are settings for configuring the Scene");     
		ImGui::Checkbox("Show Demo Window", &show_demo_window);  // Edit bools storing our window open/close state

		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button(animationButtonLabel)) // Buttons return true when clicked (most widgets return true when edited/activated)
		{
			if (!isAnimationPaused)
			{
				animationButtonLabel = "Resume Animation";
				isAnimationPaused = true;
				for (int i = 0; i < cubeList.size(); i++) {
					cubeList[i]->setAnimSpeed(0.0f);
				}
			}
			else
			{
				animationButtonLabel = "Pause Animation";
				isAnimationPaused = false;
				for (int i = 0; i < cubeList.size(); i++) {
					cubeList[i]->setAnimSpeed(1.0f);
				}
			}
		}

		
	}
	ImGui::End();
	*/


	ticks += EngineTime::getDeltaTime() * 1.0f;

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, clear_color.x, clear_color.y, clear_color.z, 1);

	RECT rc = getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	//updateCamera();
	SceneCameraHandler::getInstance()->update(EngineTime::getDeltaTime());

	// UI Updates
	UIManager::getInstance()->drawAllUI(shader_byte_code, size_shader);

	// Game Object Updates
	/*
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i]->update(EngineTime::getDeltaTime());
		cubeList[i]->draw(width, height, m_vertex_shader, m_pixel_shader);
	}
	*/
	GameObjectManager::getInstance()->updateAll(EngineTime::getDeltaTime());
	GameObjectManager::getInstance()->renderAll(width, height, m_vertex_shader, m_pixel_shader);

	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls swapchain's Present() function)

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

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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