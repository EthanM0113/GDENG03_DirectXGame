#pragma once
#include "Cube.h"
#include "TexturedVertexBuffer.h"
#include "Vector2D.h"

class ObjectRenderer;
class TexturedCube : public Cube
{
public:
	TexturedCube(String name, bool skipInit = false);
	~TexturedCube();

	void attachRenderer(ObjectRenderer* renderer);
	void draw(int width, int height) override;
	ObjectRenderer* getRenderer() const;

protected:
	TexturedVertexBuffer* vertexBuffer;
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};

	ObjectRenderer* renderer;
};