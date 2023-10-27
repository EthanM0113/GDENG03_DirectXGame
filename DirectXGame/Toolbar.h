#pragma once
#include "AUIScreen.h"

class Toolbar : public AUIScreen
{
public:
	Toolbar(String name);
	~Toolbar();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;
};

