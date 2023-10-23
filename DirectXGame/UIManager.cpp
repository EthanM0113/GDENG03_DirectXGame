#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;
UINames uiNames;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
    delete sharedInstance;
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++) {
        uiList[i]->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


UIManager::UIManager(HWND windowHandle)
{
    Toolbar* toolbar = new Toolbar(uiNames.MENU_SCREEN);
    uiList.push_back(toolbar);
}

UIManager::~UIManager()
{
}
