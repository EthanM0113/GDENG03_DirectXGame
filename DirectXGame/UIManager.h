#pragma once
#include <string>
#include <vector>
#include "AUIScreen.h"
#include <unordered_map>

#include "imfilebrowser.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Window.h"
#include "Toolbar.h"
#include "UINames.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI(void* shaderByteCode, size_t sizeShader);
	void setEnabled(String uiName, bool isPopupOpen);

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

	AUIScreen* findUIByName(String uiName);

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;
	ImGui::FileBrowser fileDialog;

	UIList uiList;
	UITable uiTable;
};

