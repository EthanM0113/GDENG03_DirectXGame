#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "ObjectRenderer.h"
#include "TexturedCube.h"
#include "TextureManager.h"
#include <string>
#include <algorithm>

#include "MaterialScreen.h"
#include "UIManager.h"
#include "UINames.h"


InspectorWindow::InspectorWindow(String name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI(void* shaderByteCode, size_t sizeShader)
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();

	ImGui::SetNextWindowSize(ImVec2(300, 1080));
	ImGui::Begin("Inspector Window", nullptr, ImGuiWindowFlags_NoResize);
	{
		if(gameObjManager->getSelectedObject() == nullptr)
			ImGui::Text("No object selected. Select an object from the scene.");
		else
		{
			// Game object was selected
			AGameObject* selectedObj = gameObjManager->getSelectedObject();
			ImGui::Text("Selected Object:");
			ImGui::SameLine();
			ImGui::Text(selectedObj->getName().c_str());

			// Set Enabled Bool
			bool enabled = selectedObj->getEnabled();
			ImGui::Checkbox("Enabled", &enabled);
			selectedObj->setEnabled(enabled);

			// Change Position
			Vector3D vector3DPos = selectedObj->getLocalPosition();
			float newPos[4] = { vector3DPos.getValues().x, vector3DPos.getValues().y, vector3DPos.getValues().z, 1.0f };
			ImGui::DragFloat3("Position", newPos, 0.1f);
			selectedObj->setPosition(Vector3D(newPos[0], newPos[1], newPos[2]));

			// Change Rotation
			Vector3D vector3DRot = selectedObj->getLocalRotation();
			float newRot[4] = { vector3DRot.getValues().x, vector3DRot.getValues().y, vector3DRot.getValues().z, 1.0f };
			ImGui::DragFloat3("Rotation", newRot, 0.01f);
			selectedObj->setRotation(Vector3D(newRot[0], newRot[1], newRot[2]));

			// Change Scale
			Vector3D vector3DScale = selectedObj->getLocalScale();
			float newScale[4] = { vector3DScale.getValues().x, vector3DScale.getValues().y, vector3DScale.getValues().z, 1.0f };
			ImGui::DragFloat3("Scale", newScale, 0.1f);
			selectedObj->setScale(Vector3D(newScale[0], newScale[1], newScale[2]));

			// Draw Materials Tab
			drawMaterialsTab();
		}
	}
	ImGui::End();
}

void InspectorWindow::drawMaterialsTab()
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();

	int BUTTON_WIDTH = 225;
	int BUTTON_HEIGHT = 20;

	if(gameObjManager->getSelectedObject()->getObjectType() != TEXTURED_CUBE)
	{
		return;
	}

	TexturedCube* texturedObj = static_cast<TexturedCube*>(gameObjManager->getSelectedObject());
	this->materialPath = texturedObj->getRenderer()->getMaterialPath();
	this->FormatMatImage();
	ImGui::SetCursorPosX(50);
	ImGui::Image(static_cast<void*>(materialDisplay->getShaderResource()), ImVec2(150, 150));

	// replace '\' with '/'
	std::replace(materialPath.begin(), materialPath.end(), '\\', '/');

	//Get file name from path
	std::string outputName;
	for(int i = materialPath.length(); i > 0; i--)
	{
		if (materialPath[i] != '/')
		{
			outputName.insert(outputName.begin(), materialPath[i]);
		}
		else
		{
			i = 0;
		}
	}

	materialName = outputName;
	std::string displayText = "Material: ";
	displayText.append(materialName);
	ImGui::Text(displayText.c_str());
	if(ImGui::Button("Add Material", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
	{
		popupOpen = !popupOpen;
		std::cout << "Popup Open: " << popupOpen << std::endl;
		UINames uiNames;
		MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
		materialScreen->linkInspectorScreen(this, materialPath);
		UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, popupOpen);
	}
}

void InspectorWindow::FormatMatImage()
{
	// covert to wchar
	std::string textureString = this->materialPath;
	std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	const wchar_t* texturePath = widestr.c_str();
	this->materialDisplay = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}

void InspectorWindow::SendResult(std::string materialPath)
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();
	TexturedCube* texturedObj = static_cast<TexturedCube*>(gameObjManager->getSelectedObject());
	texturedObj->getRenderer()->setRenderer(materialPath);
	this->popupOpen = false;
}
