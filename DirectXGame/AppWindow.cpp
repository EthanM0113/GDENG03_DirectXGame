#include "AppWindow.h"


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

	vertex quad_1_coords[] =
	{
		{-0.8f, 0.5f, 0.0f}, // POS 1 (bottom left)
		{-0.8f, 0.8f, 0.0f}, // POS 2 (top left)
		{-0.5f, 0.5f, 0.0f}, // POS 3 (bottom right)
		{-0.5f, 0.8f, 0.0f} // POS 4 (top right)
	};
	quad_1->InitializeQuad(quad_1_coords);

	vertex quad_2_coords[] =
	{
		{-0.8f, -0.8f, 0.0f}, // POS 1
		{-0.9f, 0.4f, 0.0f}, // POS 2
		{0.6f, -0.7f, 0.0f}, // POS 3
		{0.4f, 0.2f, 0.0f} // POS 4
	};
	quad_2->InitializeQuad(quad_2_coords);

	vertex quad_3_coords[] =
	{
		{0.5f, 0.2f, 0.0f}, // POS 1
		{0.2f, 0.8f, 0.0f}, // POS 2
		{0.8f, 0.5f, 0.0f}, // POS 3
		{0.8f, 0.8f, 0.0f} // POS 4
	};
	quad_3->InitializeQuad(quad_3_coords);

}
 
void AppWindow::onUpdate()
{
	//Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0, 1, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->setShaders();

	// Draw Primitives
	//triangle_1->DrawTriangle();
	quad_1->DrawQuad();
	quad_2->DrawQuad();
	quad_3->DrawQuad();

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//triangle_1->GetVertexBuffer()->release();
	quad_1->GetVertexBuffer()->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}
