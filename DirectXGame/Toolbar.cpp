#include "Toolbar.h"

Toolbar::Toolbar(String name) : AUIScreen(name)
{
}

Toolbar::~Toolbar()
{
}

void Toolbar::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(1920, 150));
	ImGui::Begin(" ", nullptr, ImGuiWindowFlags_MenuBar);
	if(ImGui::BeginMenuBar())
	{
		if(ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "?")) {}
			if (ImGui::MenuItem("Save", "??")) {}
			if (ImGui::MenuItem("Open", "???")) {}
			if (ImGui::MenuItem("Exit", "????")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}


	ImGui::End();
}
