#pragma once
#include "AUIScreen.h"

class SceneOutliner : public AUIScreen
{
public:
	SceneOutliner(String name);
	~SceneOutliner();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;
};

