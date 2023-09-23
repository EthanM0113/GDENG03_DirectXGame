#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "TrianglePrimitive.h"
#include "QuadPrimitive.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	SwapChain* m_swap_chain;
	//VertexBuffer* m_vb;

	// Primitives
	QuadPrimitive* quad_1 = new QuadPrimitive();
	QuadPrimitive* rgb_quad = new QuadPrimitive();
	QuadPrimitive* quad_3 = new QuadPrimitive();
};

