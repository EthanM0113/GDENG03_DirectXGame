#include "QuadPrimitive.h"

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

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

	constant cc;
	cc.m_angle = 0;

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
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57 * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

