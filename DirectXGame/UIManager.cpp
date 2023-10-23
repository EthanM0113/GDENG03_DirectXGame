#include "UIManager.h"

#include "EngineProfiler.h"
#include "InspectorWindow.h"
#include "SceneOutliner.h"

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
    // Add Toolbar (Menu)
    Toolbar* toolbar = new Toolbar(uiNames.MENU_SCREEN);
    uiList.push_back(toolbar);

    // Add Scene Outliner
    SceneOutliner* sceneOutliner = new SceneOutliner(uiNames.HIERARCHY_SCREEN);
    uiList.push_back(sceneOutliner);

    // Add Inspector Window
    InspectorWindow* inspectorWindow = new InspectorWindow(uiNames.INSPECTOR_SCREEN);
    uiList.push_back(inspectorWindow);

    // Add Engine Profiler
    EngineProfiler* engineProfiler = new EngineProfiler(uiNames.PROFILER_SCREEN);
    uiList.push_back(engineProfiler);
}

UIManager::~UIManager()
{
}