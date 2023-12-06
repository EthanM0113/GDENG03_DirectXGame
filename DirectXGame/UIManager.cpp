#include "UIManager.h"

#include "EngineProfiler.h"
#include "InspectorWindow.h"
#include "MaterialScreen.h"
#include "SceneOutliner.h"
#include "ScenePlayWindow.h"
#include "ActionWindow.h"

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

void UIManager::drawAllUI(void* shaderByteCode, size_t sizeShader)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++) {
        if(uiList[i]->getEnabled())
        {
            uiList[i]->drawUI(shaderByteCode, sizeShader);
        }
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::setEnabled(String uiName, bool isPopupOpen)
{
    for (int i = 0; i < this->uiList.size(); i++) {
        if(uiList[i]->getName() == uiName)
        {
            uiList[i]->setEnabled(isPopupOpen);
        }
    }
}


AUIScreen* UIManager::findUIByName(String uiName)
{
    for (int i = 0; i < this->uiList.size(); i++) {
        if (uiList[i]->getName() == uiName)
            return uiList[i];
    }

    return NULL;
}

UIManager::UIManager(HWND windowHandle)
{
    // Setup File Explorer
    fileDialog.SetTitle("Open Scene");
    fileDialog.SetTypeFilters({ ".jpg", ".png" });

    // Add Menu Bar
    MenuBar* toolbar = new MenuBar(uiNames.MENU_SCREEN);
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

    // Add Scene Play Window
    ScenePlayWindow* scenePlayWindow = new ScenePlayWindow(uiNames.SCENEPLAY_SCREEN);
    uiList.push_back(scenePlayWindow);

    // Add Material Screen Window
    MaterialScreen* materialScreen = new MaterialScreen(uiNames.MATERIAL_SCREEN, fileDialog);
    materialScreen->setEnabled(false);
    uiList.push_back(materialScreen);

    // Add Action Window
    ActionWindow* actionWindow = new ActionWindow(uiNames.ACTION_SCREEN);
    uiList.push_back(actionWindow);
}

UIManager::~UIManager()
{
}
