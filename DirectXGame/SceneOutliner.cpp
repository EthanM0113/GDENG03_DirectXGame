#include "SceneOutliner.h"

#include "GameObjectManager.h"

SceneOutliner::SceneOutliner(String name) : AUIScreen(name)
{

}

SceneOutliner::~SceneOutliner()
{

}

void SceneOutliner::drawUI(void* shaderByteCode, size_t sizeShader)
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();

	ImGui::SetNextWindowSize(ImVec2(300, 1080));
	ImGui::Begin("Scene Outliner", nullptr, ImGuiWindowFlags_NoResize);
	{
		if(gameObjManager->activeObjects() != 0)
		{
			GameObjectManager::List objList = gameObjManager->getAllObjects();

			for(int i = 0; i < gameObjManager->activeObjects(); i++)
			{
				if (ImGui::Button(objList[i]->getName().c_str(), ImVec2(-1.0f, 0.0f)))
				{
					gameObjManager->setSelectedObject(objList[i]->getName());
				}
			}
		}
	}
	ImGui::End();
}
