#include "Toolbar.h"

Toolbar::Toolbar(String name) : AUIScreen(name)
{
}

Toolbar::~Toolbar()
{
}

void Toolbar::drawUI()
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
				
			}
			if (ImGui::MenuItem("Create Sphere")) {}
			if (ImGui::MenuItem("Create Plane")) {}
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
