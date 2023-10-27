#include "Toolbar.h"

#include "Cube.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "Plane.h"

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
			if (ImGui::MenuItem("Create Cube"))
			{
				void* shaderByteCode = nullptr;
				size_t sizeShader = 0;
				GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shaderByteCode, sizeShader);
			}
			if (ImGui::MenuItem("Create Sphere")) {}
			if (ImGui::MenuItem("Create Plane"))
			{
				void* shaderByteCode = nullptr;
				size_t sizeShader = 0;
				GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shaderByteCode, sizeShader);
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
