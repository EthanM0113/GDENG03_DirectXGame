#include "SceneWriter.h"
#include <iostream>
#include <fstream>

#include "AGameObject.h"
#include "GameObjectManager.h"
#include "ObjectRenderer.h"
#include "TexturedCube.h"


SceneWriter::SceneWriter()
{
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::writeToFile(std::string filePath)
{
	std::string directory = filePath;
	std::string fileDir;
	fileDir = directory;
	fileDir.append(".iet");

	if(directory.find(".iet") != std::string::npos)
	{
		fileDir = directory;
	}

	std::ofstream sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	//std::cout << "Selected filename " << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

	for(int i = 0; i < allObjects.size(); i++)
	{
		sceneFile << allObjects[i]->getName() << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "Type: " << allObjects[i]->getObjectType() << std::endl;
		sceneFile << "Position: " << position.getValues().x << " " << position.getValues().y << " " << position.getValues().z << std::endl;
		sceneFile << "Rotation: " << rotation.getValues().x << " " << rotation.getValues().y << " " << rotation.getValues().z << std::endl;
		sceneFile << "Scale: " << scale.getValues().x << " " << scale.getValues().y << " " << scale.getValues().z << std::endl;

		// Write Material Path for Textured Cubes
		if(allObjects[i]->getObjectType() == TEXTURED_CUBE)
		{
			TexturedCube* textureCube = (TexturedCube*)allObjects[i];
			sceneFile << textureCube->getRenderer()->getMaterialPath() << std::endl;
		}

	}

	// Get game object counts
	sceneFile << "CubeCount: " << GameObjectManager::getInstance()->getCubeCount() << std::endl;
	sceneFile << "PlaneCount: " << GameObjectManager::getInstance()->getPlaneCount() << std::endl;
	sceneFile << "PhysicsCubeCount: " << GameObjectManager::getInstance()->getPhysicsCubeCount() << std::endl;
	sceneFile << "PhysicsPlaneCount: " << GameObjectManager::getInstance()->getPhysicsPlaneCount() << std::endl;
	sceneFile << "TexturedCubeCount: " << GameObjectManager::getInstance()->getTexturedCubeCount() << std::endl;
	sceneFile.close();

	std::cout << "Finished Writing" << std::endl;
}


