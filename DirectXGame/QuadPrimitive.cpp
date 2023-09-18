#include "QuadPrimitive.h"

QuadPrimitive::QuadPrimitive()
{

}

void QuadPrimitive::InitializeQuad(vertex positions[4])
{
	list[0] = positions[0];
	list[1] = positions[1];
	list[2] = positions[2];
	list[3] = positions[3];

	shader_byte_code = nullptr;
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();
	size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
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

void QuadPrimitive::DrawQuad()
{
	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

