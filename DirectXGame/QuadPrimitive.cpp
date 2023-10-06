#include "QuadPrimitive.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include <iostream>

#include "EngineTime.h"

using namespace std;

QuadPrimitive::QuadPrimitive()
{

}

void QuadPrimitive::InitializeQuad(vertex positions[maxLimit])
{
	list[0] = positions[0];
	list[1] = positions[1];
	list[2] = positions[2];
	list[3] = positions[3];

	m_vb = GraphicsEngine::get()->createVertexBuffer();
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
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

QuadPrimitive::~QuadPrimitive()
{

}

UINT QuadPrimitive::GetListSize()
{
	UINT size_list = ARRAYSIZE(list);
	return size_list;
}

vertex* QuadPrimitive::GetVertexList()
{
	return list;
}

VertexBuffer* QuadPrimitive::GetVertexBuffer()
{
	return m_vb;
}

void QuadPrimitive::ReleaseBuffer()
{
	m_vb->release();
}

void QuadPrimitive::ReleaseShaders()
{
	m_vs->release();
	m_ps->release();
}

void QuadPrimitive::UpdateQuadPosition(RECT rc, float m_delta_time)
{
	/* For HO
	//time ++ 1.57 * EngineTime::getDeltaTime();
	
	time += EngineTime::getDeltaTime();
	speed = (maxSpeed * (sin(time * 0.1)));
	constant cc;
	cc.time= speed;
	*/

	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.15f;

	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	cc.m_world *= temp;


	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(rc.right - rc.left) / 400.0f,
		(rc.bottom - rc.top) / 400.0f,
		-4.0f,
		4.0f
	);


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

}

