#include "ActionWindow.h"
#include "ActionHistory.h"

ActionWindow::ActionWindow(String name) : AUIScreen(name)
{

}

ActionWindow::~ActionWindow()
{
}

void ActionWindow::drawUI(void* shaderByteCode, size_t sizeShader)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(200, 80));
	ImGui::Begin("Actions", nullptr, ImGuiWindowFlags_None);
	{
		if (ImGui::Button("Undo"))
		{
			ActionHistory::getInstance()->undoLatestAction();
		}
		ImGui::SameLine();
		if (ImGui::Button("Redo"))
		{
			ActionHistory::getInstance()->redoLatestAction();
		}
	}
	ImGui::End();
}
