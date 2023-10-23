#include "InspectorWindow.h"

InspectorWindow::InspectorWindow(String name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(300, 1080));
	ImGui::Begin("Inspector Window", nullptr, ImGuiWindowFlags_NoResize);
	{
		ImGui::Text("No object selected. Select an object from the scene.");
	}
	ImGui::End();
}
