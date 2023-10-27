#pragma once
#include "AUIScreen.h"

class EngineProfiler : public AUIScreen
{
public:
	EngineProfiler(String name);
	~EngineProfiler();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;
};

