#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_time;
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

