#include "ScenePlayWindow.h"

#include "BaseComponentSystem.h"
#include "EngineBackend.h"

ScenePlayWindow::ScenePlayWindow(String name) : AUIScreen(name)
{
}

ScenePlayWindow::~ScenePlayWindow()
{
}

void ScenePlayWindow::drawUI(void* shaderByteCode, size_t sizeShader)
{
	EngineBackend* backend = EngineBackend::getInstance();

	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(200, 80));
	ImGui::Begin("Scene Play Options", nullptr, ImGuiWindowFlags_None);
	{
		if (ImGui::Button(sleepButtonLabel)) 
		{
			if(backend->getMode() == EngineBackend::EDITOR)
			{
				backend->setMode(EngineBackend::PLAY);
				isSleeping = false;
				sleepButtonLabel = "Stop";
			}
			else if(backend->getMode() == EngineBackend::PLAY) 
			{
				// Should reset physics objects but right now buggy, dont stop after playing
				sleepButtonLabel = "Play";
			}
		}
		if(!isSleeping)
		{
			ImGui::SameLine();
			if (ImGui::Button(pauseButtonLabel)) 
			{
				if (backend->getMode() == EngineBackend::PAUSED)
				{
					backend->setMode(EngineBackend::PLAY);
					pauseButtonLabel = "Pause";
				}
				else if (backend->getMode() == EngineBackend::PLAY)
				{
					backend->setMode(EngineBackend::PAUSED);
					pauseButtonLabel = "Resume";
				}
			}

			// Frame Step Button appears when paused
			if(backend->getMode() == EngineBackend::PAUSED)
			{
				ImGui::SameLine();
				if (ImGui::Button("Frame Step"))
				{
					backend->startFrameStep();
				}
			}
		}
	}
	ImGui::End();
}
