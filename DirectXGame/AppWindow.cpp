#include "AppWindow.h"
#include <Windows.h>

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
		{-0.8f, 0.5f, 0.0f}, // POS 1 (bottom left)
		{-0.8f, 0.8f, 0.0f}, // POS 2 (top left)
		{-0.5f, 0.5f, 0.0f}, // POS 3 (bottom right)
		{-0.5f, 0.8f, 0.0f} // POS 4 (top right)
	};
	quad_1->InitializeQuad(quad_1_coords);
	*/

	vertex rgb_quad_coords[] =
	{
		//X - Y - Z
		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS3
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 } // POS4
	};
	rgb_quad->InitializeQuad(rgb_quad_coords);

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
