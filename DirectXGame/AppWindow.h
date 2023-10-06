#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Matrix4x4.h"
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

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

// Cube Stuff
private:
	constant cc;
	Matrix4x4 temp;
	void UpdateQuadPosition(float m_delta_time);
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
	UINT size_list;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;


};

