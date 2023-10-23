#pragma once
#include "AUIScreen.h"

class InspectorWindow : public AUIScreen
{
public:
	InspectorWindow(String name);
	~InspectorWindow();

	void drawUI() override;
};

