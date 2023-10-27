#include "InspectorWindow.h"

#include "GameObjectManager.h"

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
			ImGui::InputFloat3("Position", newPos);
			selectedObj->setPosition(Vector3D(newPos[0], newPos[1], newPos[2]));

			// Change Rotation
			Vector3D vector3DRot = selectedObj->getLocalRotation();
			float newRot[4] = { vector3DRot.getValues().x, vector3DRot.getValues().y, vector3DRot.getValues().z, 1.0f };
			ImGui::InputFloat3("Rotation", newRot);
			selectedObj->setRotation(Vector3D(newRot[0], newRot[1], newRot[2]));

			// Change Scale
			Vector3D vector3DScale = selectedObj->getLocalScale();
			float newScale[4] = { vector3DScale.getValues().x, vector3DScale.getValues().y, vector3DScale.getValues().z, 1.0f };
			ImGui::InputFloat3("Scale", newScale);
			selectedObj->setScale(Vector3D(newScale[0], newScale[1], newScale[2]));

		}
	}
	ImGui::End();
}
