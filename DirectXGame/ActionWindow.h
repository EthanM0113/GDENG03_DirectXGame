#pragma once
#include "AUIScreen.h"

class ActionWindow : public AUIScreen
{
public:
	ActionWindow(String name);
	~ActionWindow();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;
};

