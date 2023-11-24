#pragma once
#include "Cube.h"

//Plane implementation is just like cube with different scale
class Plane : public Cube
{
public:
	Plane(string name);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

};