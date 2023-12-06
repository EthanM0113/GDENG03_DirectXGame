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
	void drawRigidbodyTab();
	void FormatMatImage();
	void SendResult(std::string materialPath);
	void onTransformUpdate();
	void resetForceVector();

private:
	std::string materialPath;
	std::string materialName;
	std::string displayTex;
	Texture* materialDisplay;
	bool popupOpen = false;

	// Transform variables
	float newPos[4];
	float newRot[4];
	float newScale[4];

	float newForceVector[4] = { 0, 0, 0, 1.0f };
};

