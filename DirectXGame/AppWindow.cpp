#include "AppWindow.h"
#include <Windows.h>

#include "EngineTime.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// Create Primitives
	//Triangle Primitive Example
	/*
	vertex triangle_1_coords[] =
	{
		{-0.5f, -0.5f, 0.0f}, // POS 1
		{0.0f, 0.5f, 0.0f}, // POS 2
		{0.5f, -0.5f, 0.0f} // POS 3
	};
	triangle_1->InitializeTriangle(triangle_1_coords);
	*/

	/*
	vertex quad_1_coords[] =
	{
		{-0.8f, 0.5f, 0.0f,		-0.6f,0.30f,0.0f,	0,0,0,	0,1,0 }, // POS 1 (bottom left)
		{-0.8f, 0.8f, 0.0f,		-0.6f,0.70f,0.0f,	1,1,0,	0,1,1 }, // POS 2 (top left)
		{-0.5f, 0.5f, 0.0f,		-0.4f,0.2f,0.0f,	0,0,1,	1,0,0 }, // POS 3 (bottom right)
		{-0.5f, 0.8f, 0.0f,		-0.46,0.7f,0.0f,	1,1,1,	0,0,1 } // POS 4 (top right)
	};
	quad_1->InitializeQuad(quad_1_coords);
	quadList.push_back(quad_1);
	*/

	vertex rgb_quad_coords[] =
	{
		//X - Y - Z
		{-0.7f,-0.9f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.9f,0.1f,0.0f,     -0.11f,0.68f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.9f,-0.4f,0.0f,     0.1f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS3
		{ -0.7f,-0.9f,0.0f,      0.8f,0.7f,1.0f,    1,1,1,  0,0,1 } // POS4
	};
	rgb_quad->InitializeQuad(rgb_quad_coords);
	quadList.push_back(rgb_quad);

	/*
	vertex quad_3_coords[] =
	{

		{0.2f, 0.2f, 0.0f}, // POS 1
		{0.2f, 0.8f, 0.0f}, // POS 2
		{0.8f, 0.2f, 0.0f}, // POS 3
		{0.8f, 0.8f, 0.0f} // POS 4
	};
	quad_3->InitializeQuad(quad_3_coords);
	*/


}
 
void AppWindow::onUpdate()
{
	// Clear Render Target
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 0.3, 1);

	// Set Viewport
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Draw Primitives
	//triangle_1->DrawTriangle();
	//quad_1->UpdateQuad();
	rgb_quad->UpdateQuad();
	//quad_3->UpdateQuad();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//triangle_1->GetVertexBuffer()->release();
	//quad_1->ReleaseBuffer();
	rgb_quad->ReleaseBuffer();
	//quad_3->ReleaseBuffer();
	m_swap_chain->release();
	//quad_1->ReleaseShaders();
	rgb_quad->ReleaseShaders();
	//quad_3->ReleaseShaders();
	GraphicsEngine::get()->release();
}


void AppWindow::initializeQuadList()
{
	/*
	// Single Vertex Buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	

	for (int i = 0; i < quadList.size(); i++)
	{
		vertex* list = quadList[i]->GetVertexList();

		size_list = ARRAYSIZE(list);

		shader_byte_code = nullptr;
		size_shader = 0;
		//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

		GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
		m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
		m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

		GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
		m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
		GraphicsEngine::get()->releaseCompiledShader();

		constant cc;
		cc.m_angle = 0;

		m_cb = GraphicsEngine::get()->createConstantBuffer();
		m_cb->load(&cc, sizeof(constant));

	}
	*/
}

void AppWindow::updateQuadList()
{
	for (int i = 0; i < quadList.size(); i++)
	{

	}


}


