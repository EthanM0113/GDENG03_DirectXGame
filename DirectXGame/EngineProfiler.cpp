#include "EngineProfiler.h"

EngineProfiler::EngineProfiler(String name) : AUIScreen(name)
{
}

EngineProfiler::~EngineProfiler()
{
}

void EngineProfiler::drawUI(void* shaderByteCode, size_t sizeShader)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(340, 80));
	ImGui::Begin("GDENG03 Engine Profiler", nullptr, ImGuiWindowFlags_None);
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);	}
	ImGui::End();
}
