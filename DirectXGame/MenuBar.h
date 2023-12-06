#pragma once
#include "AUIScreen.h"
#include "imfilebrowser.h"
#include "SceneWriter.h"
#include "SceneReader.h"

class MenuBar : public AUIScreen
{
public:
	MenuBar(String name);
	~MenuBar();

	void drawUI(void* shaderByteCode, size_t sizeShader) override;

private:
	SceneWriter* sceneWriter;
	SceneReader* sceneReader;
	ImGui::FileBrowser* saveDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	ImGui::FileBrowser* loadDialog = new ImGui::FileBrowser();
};

