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
	vertex* GetVertexList();
	VertexBuffer* GetVertexBuffer();
	void ReleaseBuffer();
	void ReleaseShaders();
	void UpdateQuadPosition(RECT rc, float m_delta_time);

private:
	static const int maxLimit = 4;
	UINT size_list;
	size_t size_shader;
	vertex list[maxLimit];
	void* shader_byte_code;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	float time = 0;
	float speed = 0;
	const float maxSpeed = 100.0f;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
};

