#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "TrianglePrimitive.h"
#include "QuadPrimitive.h"
#include <vector>

using namespace std;

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
	
	// Primitives
	QuadPrimitive* quad_1 = new QuadPrimitive();
	QuadPrimitive* rgb_quad = new QuadPrimitive();
	QuadPrimitive* quad_3 = new QuadPrimitive();

	// Main Vertex Buffer
	VertexBuffer* m_vb;
	UINT size_list;
	vector<QuadPrimitive*> quadList;
	void initializeQuadList();
	void updateQuadList(); // Update and Draw Methods

	
};

