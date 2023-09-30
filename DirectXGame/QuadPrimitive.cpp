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

void QuadPrimitive::InitializeQuad(vertex positions[4])
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

	CBData cc;
	cc.time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(CBData));
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

void QuadPrimitive::UpdateQuad()
{
	//time ++ 1.57 * EngineTime::getDeltaTime();
	time += EngineTime::getDeltaTime();
	speed = (maxSpeed * (sin(time * 0.1)));
	CBData cc;
	cc.time= speed;

	//cout << "Time: " << time << endl;
	//cout << "Speed : " << speed << endl;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

}

