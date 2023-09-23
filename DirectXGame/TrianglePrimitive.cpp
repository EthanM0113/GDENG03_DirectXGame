#include "TrianglePrimitive.h"
#include <iostream>

TrianglePrimitive::TrianglePrimitive()
{
}


void TrianglePrimitive::InitializeTriangle(vertex positions[3])
{
	list[0] = positions[0];
	list[1] = positions[1];
	list[2] = positions[2];

	shader_byte_code = nullptr;
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	size_list = ARRAYSIZE(list);


	size_shader = 0;

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	
}


TrianglePrimitive::~TrianglePrimitive()
{

}

UINT TrianglePrimitive::GetListSize()
{
	UINT size_list = ARRAYSIZE(list);
	return size_list;
}

VertexBuffer* TrianglePrimitive::GetVertexBuffer()
{
	return m_vb;
}

void TrianglePrimitive::DrawTriangle()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
}


