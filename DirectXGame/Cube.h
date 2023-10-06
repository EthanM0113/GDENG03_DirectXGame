#pragma once
#include "GameObject.h"
#include "TrianglePrimitive.h"

class Cube : public GameObject
{
public:
	Cube();
	~Cube();
	void Initialize(vertex *vertex_list);
	void SetAnimationSpeed(float newAnimationSpeed);
	void Update(float m_delta_time, RECT rc);
	void Draw();
	void Release();

private:
	float animationSpeed = 1.0;
};

