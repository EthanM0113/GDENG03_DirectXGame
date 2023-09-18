#pragma once
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "TrianglePrimitive.h"

class QuadPrimitive
{
public:
	QuadPrimitive();
	~QuadPrimitive();
	void InitializeQuad(vertex positions[4]);
	UINT GetListSize();
	VertexBuffer* GetVertexBuffer();
	void DrawQuad();

private:
	static const int maxLimit = 4;
	UINT size_list;
	UINT size_shader;
	vertex list[maxLimit];
	void* shader_byte_code;
	VertexBuffer* m_vb;

};

