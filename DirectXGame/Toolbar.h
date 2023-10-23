#pragma once
#include "AUIScreen.h"

class Toolbar : public AUIScreen
{
public:
	Toolbar(String name);
	~Toolbar();

	void drawUI() override;
};

