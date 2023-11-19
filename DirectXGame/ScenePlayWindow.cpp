#include "ScenePlayWindow.h"

#include "BaseComponentSystem.h"

ScenePlayWindow::ScenePlayWindow(String name) : AUIScreen(name)
{
}

ScenePlayWindow::~ScenePlayWindow()
{
}

void ScenePlayWindow::drawUI(void* shaderByteCode, size_t sizeShader)
{
	if(isSleeping)
	{
		BaseComponentSystem::getInstance()->getPhysicsSystem()->setSleepOfAllComponents(true);
	}
	else if(!isSleeping)
	{
		BaseComponentSystem::getInstance()->getPhysicsSystem()->setSleepOfAllComponents(false);
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(200, 80));
	ImGui::Begin("Scene Play Options", nullptr, ImGuiWindowFlags_None);
	{
		if (ImGui::Button(sleepButtonLabel)) // Buttons return true when clicked (most widgets return true when edited/activated)
		{
			if(isSleeping)
			{
				isSleeping = false;
				sleepButtonLabel = "Stop";
			}
			else if(!isSleeping)
			{
				isSleeping = true;
				sleepButtonLabel = "Play";
			}
		}
	}
	ImGui::End();
}
