#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "ObjectRenderer.h"
#include "TexturedCube.h"
#include "TextureManager.h"
#include <string>
#include <algorithm>

#include "ActionHistory.h"
#include "MaterialScreen.h"
#include "UIManager.h"
#include "UINames.h"

#include "AGameObject.h"
#include "PhysicsComponent.h"


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
		if (gameObjManager->getSelectedObject() == nullptr)
			ImGui::Text("No object selected. Select an object from the scene.");
		else
		{
			// Game object was selected
			AGameObject* selectedObj = gameObjManager->getSelectedObject();
			ImGui::Text("Selected Object:");
			ImGui::SameLine();
			ImGui::Text(selectedObj->getName().c_str());

			// Delete Button
			if (ImGui::Button("Delete", ImVec2(60, 20)))
			{
				GameObjectManager::getInstance()->deleteObject(selectedObj);
			}

			// Set Enabled Bool
			bool enabled = selectedObj->getEnabled();
			ImGui::Checkbox("Enabled", &enabled);
			selectedObj->setEnabled(enabled);

			// Change Position
			Vector3D vector3DPos = selectedObj->getLocalPosition();
			newPos[0] = vector3DPos.getValues().x;
			newPos[1] = vector3DPos.getValues().y;
			newPos[2] = vector3DPos.getValues().z;
			newPos[3] = 1.0f;
			if(ImGui::DragFloat3("Position", newPos, 0.1f))
			{
				onTransformUpdate();
			}

			// Change Rotation
			Vector3D vector3DRot = selectedObj->getLocalRotation();
			newRot[0] = vector3DRot.getValues().x;
			newRot[1] = vector3DRot.getValues().y;
			newRot[2] = vector3DRot.getValues().z;
			newRot[3] = 1.0f;
			if(ImGui::DragFloat3("Rotation", newRot, 0.1f))
			{
				onTransformUpdate();
			}

			// Change Scale
			Vector3D vector3DScale = selectedObj->getLocalScale();
			newScale[0] = vector3DScale.getValues().x;
			newScale[1] = vector3DScale.getValues().y;
			newScale[2] = vector3DScale.getValues().z;
			newScale[3] = 1.0f;
			if(ImGui::DragFloat3("Scale", newScale, 0.1f))
			{
				onTransformUpdate();
			}

			// Rigidbody Component Tab
			drawRigidbodyTab();

			// Draw Materials Tab
			drawMaterialsTab();
		}
	}
	ImGui::End();
}

void InspectorWindow::drawRigidbodyTab()
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();

	int BUTTON_WIDTH = 280;
	int BUTTON_HEIGHT = 20;

	if (gameObjManager->getSelectedObject() != nullptr)
	{
		AGameObject* selectedObj = gameObjManager->getSelectedObject();

		std::string displayText = "Rigidbody: ";
		// Display if no rigidbody
		if(selectedObj->findComponentOfType(AComponent::Physics) == nullptr)
		{
			std::string none = "None";
			displayText.append(none);
			ImGui::Text(displayText.c_str());
			if (ImGui::Button("Add Rigidbody", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
			{
				// Attach Physics Component
				std::string objectName = selectedObj->getName();
				std::string componentName = "PhysicsComponent_";
				componentName.append(objectName);
				PhysicsComponent* physicsComponent = new PhysicsComponent(componentName, selectedObj, BodyType::DYNAMIC, 3.0f);
				selectedObj->attachComponent(physicsComponent);
			}
		}
		else // Display rigidbody properties
		{
			ImGui::Text(displayText.c_str());

			// Get physics component
			PhysicsComponent* physicsComponent = (PhysicsComponent*)selectedObj->findComponentOfType(AComponent::Physics);

			// Detaching
			if (ImGui::Button("Detach", ImVec2(100, BUTTON_HEIGHT)))
			{
				selectedObj->detachComponent(physicsComponent);
			}

			// Toggles
			bool componentEnabled = physicsComponent->getIsActive();
			ImGui::Checkbox("Is Enabled", &componentEnabled);
			physicsComponent->setIsActive(componentEnabled);
			bool staticEnabled = physicsComponent->getIsStatic();
			ImGui::Checkbox("Is Static", &staticEnabled);
			physicsComponent->setIsStatic(staticEnabled);
			bool gravityEnabled = physicsComponent->getIsGravity();
			ImGui::Checkbox("Enable Gravity", &gravityEnabled);
			physicsComponent->setIsGravity(gravityEnabled);

			// Set Mass
			ImGui::Text("Set Mass: ");
			float mass = physicsComponent->getMass();
			if (ImGui::DragFloat("kg", &mass, 0.1f))
			{
				physicsComponent->setMass(mass);
				std::cout << "Mass: " << physicsComponent->getMass() << std::endl;
 			}

			// Apply Force Vector
			ImGui::Text("Apply Force Vector: ");
			ImGui::DragFloat3("", newForceVector, 0.1f);
			if (ImGui::Button("Apply Force", ImVec2(100, BUTTON_HEIGHT)))
			{
				physicsComponent->applyForce(Vector3(newForceVector[0], newForceVector[1], newForceVector[2]));
				resetForceVector();
			}
		}


	}

}


void InspectorWindow::drawMaterialsTab()
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();

	int BUTTON_WIDTH = 280;
	int BUTTON_HEIGHT = 20;

	if(gameObjManager->getSelectedObject() != nullptr)
	{
		if (gameObjManager->getSelectedObject()->getObjectType() != TEXTURED_CUBE)
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
		for (int i = materialPath.length(); i > 0; i--)
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
		if (ImGui::Button("Add Material", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
		{
			popupOpen = !popupOpen;
			std::cout << "Popup Open: " << popupOpen << std::endl;
			UINames uiNames;
			MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
			materialScreen->linkInspectorScreen(this, materialPath);
			UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, popupOpen);
		}
	}
}

void InspectorWindow::onTransformUpdate()
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();
	if (gameObjManager->getSelectedObject() != nullptr)
	{
		AGameObject* selectedObj = gameObjManager->getSelectedObject();

		// Record changes to transform in actionHistory
		ActionHistory::getInstance()->startRecordAction(selectedObj);

		selectedObj->setPosition(Vector3D(newPos[0], newPos[1], newPos[2]));
		selectedObj->setRotation(Vector3D(newRot[0], newRot[1], newRot[2]));
		selectedObj->setScale(Vector3D(newScale[0], newScale[1], newScale[2]));

		ActionHistory::getInstance()->endRecordAction();
	}
}

void InspectorWindow::resetForceVector()
{
	// Reset force vector for QoL
	newForceVector[0] = 0;
	newForceVector[1] = 0;
	newForceVector[2] = 0;
	newForceVector[3] = 1.0f;
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


