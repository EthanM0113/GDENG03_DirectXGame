#include "SceneOutliner.h"

SceneOutliner::SceneOutliner(String name) : AUIScreen(name)
{

}

SceneOutliner::~SceneOutliner()
{

}

void SceneOutliner::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(300, 1080));
	ImGui::Begin("Scene Outliner", nullptr, ImGuiWindowFlags_NoResize);
	{

	}
	ImGui::End();
}
