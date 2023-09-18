#include "Triangle.h"

Triangle::Triangle(vec3 pos1, vec3 pos2, vec3 pos3)
{
	list[0].position = pos1;
	list[1].position = pos2;
	list[2].position = pos3;

	shader_byte_code = nullptr;
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();
	size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

Triangle::~Triangle()
{

}

UINT Triangle::GetListSize()
{
	UINT size_list = ARRAYSIZE(list);
	return size_list;
}
