#pragma once
#include "AppWindow.cpp"
#include "GraphicsEngine.h"

class Triangle
{

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

public:
	Triangle(vec3 pos1, vec3 pos2, vec3 pos3);
	~Triangle();
	UINT GetListSize();

private:
	static const int maxLimit = 3;
	UINT size_list;
	UINT size_shader;
	Triangle::vertex list[maxLimit];
	void* shader_byte_code;
	VertexBuffer* m_vb;


};

