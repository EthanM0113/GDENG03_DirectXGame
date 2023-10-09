#pragma once
#include "Matrix4x4.h"
#include "TrianglePrimitive.h"
#include "Vector3D.h"

class AGameObject
{
public:
	void SetOrigin(Vector3D originalPos);
	void SetScale(Vector3D newScale);

	// private variables, but public to children
protected:
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	// Transform Stuff
	static const int maxLimit = 8; // if more game objects with different faces, might change this implementation
	vertex list[maxLimit];
	UINT size_list;
	constant cc;
	vertex vertex_list;
	Vector3D origin;
	Vector3D scale;
	Matrix4x4 temp;
};

