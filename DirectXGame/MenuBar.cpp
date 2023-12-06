#include "MenuBar.h"

#include <iostream>

#include "GameObjectManager.h"
#include "Vector3D.h"


MenuBar::MenuBar(String name) : AUIScreen(name)
{
	SceneWriter* sceneWriter = new SceneWriter();

	// Setup Save Scene Explorer
	saveDialog->SetTitle("Save Scene");
	saveDialog->SetTypeFilters({".iet"});

	// Setup Load Scene Explorer
	loadDialog->SetTitle("Load Scene");
	loadDialog->SetTypeFilters({".iet"});
}

MenuBar::~MenuBar()
{
}

void MenuBar::drawUI(void* shaderByteCode, size_t sizeShader)
{
	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Save Scene"))
			{
				saveDialog->Open();
			}
			if (ImGui::MenuItem("Open Scene"))
			{
				loadDialog->Open();
			}
			if (ImGui::MenuItem("Exit")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject"))
		{
			void* shaderByteCode = nullptr;
			size_t sizeShader = 0;

			if (ImGui::MenuItem("Create Cube"))
			{
				GameObjectManager::getInstance()->createObject(PrimitiveType::CUBE);
			}
			if (ImGui::MenuItem("Create Textured Cube"))
			{
				GameObjectManager::getInstance()->createObject(PrimitiveType::TEXTURED_CUBE);
			}
			if (ImGui::MenuItem("Create Physics Cube"))
			{
				GameObjectManager::getInstance()->createObject(PrimitiveType::PHYSICS_CUBE);
			}
			if (ImGui::MenuItem("Create Sphere")) {}
			if (ImGui::MenuItem("Create Plane"))
			{
				GameObjectManager::getInstance()->createObject(PrimitiveType::PLANE);
			}
			if (ImGui::MenuItem("Create Physics Plane"))
			{
				GameObjectManager::getInstance()->createObject(PrimitiveType::PHYSICS_PLANE);
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

	// Open Save Scene Dialog
	saveDialog->Display();
	if (saveDialog->HasSelected())
	{
		std::cout << "Selected filename" << saveDialog->GetSelected().string() << std::endl;
		sceneWriter->writeToFile(saveDialog->GetSelected().string()); // set file path as selected path
		saveDialog->ClearSelected();
	}

	// Open Load Scene Dialog
	loadDialog->Display();
	if (loadDialog->HasSelected())
	{
		std::cout << "Selected filename: " << loadDialog->GetSelected().string() << std::endl;
		sceneReader->loadFromFile(loadDialog->GetSelected().string());
		loadDialog->ClearSelected();
	}
}
