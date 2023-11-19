#pragma once
#include "AUIScreen.h"

class ScenePlayWindow : public AUIScreen
{
public:
	ScenePlayWindow(String name);
	~ScenePlayWindow();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;

private:
	const char* sleepButtonLabel = "Play";
	bool isSleeping = true;
};

