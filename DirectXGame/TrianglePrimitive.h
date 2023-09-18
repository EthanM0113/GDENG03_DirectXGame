#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

class TrianglePrimitive
{
public:
	TrianglePrimitive();
	~TrianglePrimitive();
	void InitializeTriangle(vertex positions[3]);
	UINT GetListSize();
	VertexBuffer* GetVertexBuffer();
	void DrawTriangle();

private:
	static const int maxLimit = 3;
	UINT size_list;
	UINT size_shader;
	vertex list[maxLimit];
	void* shader_byte_code;
	VertexBuffer* m_vb;
};

