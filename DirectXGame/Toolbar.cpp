#include "Toolbar.h"

#include "GameObjectManager.h"


Toolbar::Toolbar(String name) : AUIScreen(name)
{
}

Toolbar::~Toolbar()
{
}

void Toolbar::drawUI(void* shaderByteCode, size_t sizeShader)
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Save")) {}
			if (ImGui::MenuItem("Open")) {}
			if (ImGui::MenuItem("Exit")) {}
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("GameObject"))
		{
			void* shaderByteCode = nullptr;
			size_t sizeShader = 0;

			if (ImGui::MenuItem("Create Cube"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shaderByteCode, sizeShader);
			}
			if (ImGui::MenuItem("Create Textured Cube"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::TEXTURED_CUBE, shaderByteCode, sizeShader);
			}
			if (ImGui::MenuItem("Create Physics Cube"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE, shaderByteCode, sizeShader);
			}
			if (ImGui::MenuItem("Create Sphere")) {}
			if (ImGui::MenuItem("Create Plane"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shaderByteCode, sizeShader);
			}
			if (ImGui::MenuItem("Create Physics Plane"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE, shaderByteCode, sizeShader);
			}
			if (ImGui::BeginMenu("Light"))
			{
				ImGui::MenuItem("Point Light");
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
