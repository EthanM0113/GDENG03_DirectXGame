#pragma once
#include "AUIScreen.h"
#include "Texture.h"

class InspectorWindow : public AUIScreen
{
public:
	InspectorWindow(String name);
	~InspectorWindow();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;
	void drawMaterialsTab();
	void FormatMatImage();
	void SendResult(std::string materialPath);

private:
	std::string materialPath;
	std::string materialName;
	std::string displayTex;
	Texture* materialDisplay;
	bool popupOpen = false;
};

