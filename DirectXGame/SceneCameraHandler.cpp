#include "SceneCameraHandler.h"
#include "Camera.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
	delete sharedInstance;
}

void SceneCameraHandler::update(float deltaTime)
{
	sceneCamera->update(deltaTime);
}

void SceneCameraHandler::onFocus()
{
	sceneCamera->onFocus();
}

void SceneCameraHandler::onKillFocus()
{
	sceneCamera->onKillFocus();
}

void SceneCameraHandler::setGUIHoverFlag(bool guiHoverFlag)
{
	sceneCamera->setGUIHoverFlag(guiHoverFlag);
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return sceneCamera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
	sceneCamera = new Camera("Camera1");
}


SceneCameraHandler::~SceneCameraHandler()
{

}
