#include "SceneReader.h"
#include <iostream>
#include <fstream>

#include "AGameObject.h"
#include "GameObjectManager.h"
#include "StringUtils.h"
#include "Vector3D.h"

SceneReader::SceneReader()
{
}

SceneReader::~SceneReader()
{
}

void SceneReader::loadFromFile(std::string filePath)
{
	std::ifstream sceneFile;
	sceneFile.open(filePath, std::ios::out);

	std::string objectName;
	PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	std::string materialPath;
	std::string readLine;

	int cubeCount;
	int planeCount;
	int physicsCubeCount;
	int physicsPlaneCount;
	int texturedCubeCount;

	bool finishedGameObjects = false;

	// Delete all game objects
	GameObjectManager::getInstance()->deleteAllObjects();


	int index = 0;
	bool specialCheckCount = false;
	while (std::getline(sceneFile, readLine))
	{
		std::cout << "Index " << index << std::endl;
		// Check next line for object counts
		if (!finishedGameObjects)
		{
			if (index == 5 && readLine.find("CubeCount: ") != std::string::npos)
			{
				finishedGameObjects = true;
			}
			else if(index == 6 && specialCheckCount)
			{
				if (index == 6 && readLine.find("CubeCount: ") != std::string::npos)
				{
					finishedGameObjects = true;
					index = 5;
				}
				else
					index = 0;

				specialCheckCount = false;
			}
			else if (index == 5)
			{
				// If textured cube
				if (objectType == TEXTURED_CUBE)
				{
					materialPath = readLine;
					GameObjectManager::getInstance()->createTexturedObjectFromFile(objectName, objectType, position, rotation, scale, materialPath);

					// Check for cube count in next line
					index++;
					specialCheckCount = true;
				}
				else
				{
					index = 0;
				}
			}
		}

		if(!specialCheckCount)
		{
			if (index == 0)
			{
				objectName = readLine;
				index++;
			}
			else if (index == 1)
			{
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				objectType = (PrimitiveType)std::stoi(stringSplit[1]);
				index++;
			}
			else if (index == 2)
			{
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}
			else if (index == 3)
			{
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
			}
			else if (index == 4)
			{
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
				index++;
				if (objectType != TEXTURED_CUBE)
					GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale);
			}
			else if (index == 5)
			{
				// Get cube count
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				cubeCount = std::stoi(stringSplit[1]);

				GameObjectManager::getInstance()->setCubeCount(cubeCount);
				index++;
			}
			else if (index == 6)
			{
				// Get plane count
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				planeCount = std::stoi(stringSplit[1]);

				GameObjectManager::getInstance()->setPlaneCount(planeCount);
				index++;
			}
			else if (index == 7)
			{
				// Get physics cube count
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				physicsCubeCount = std::stoi(stringSplit[1]);

				GameObjectManager::getInstance()->setPhysicsCubeCount(physicsCubeCount);
				index++;
			}
			else if (index == 8)
			{
				// Get physics plane count
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				physicsPlaneCount = std::stoi(stringSplit[1]);

				GameObjectManager::getInstance()->setPhysicsPlaneCount(physicsPlaneCount);
				index++;
			}
			else if (index == 9)
			{
				// Get textured cube count
				std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
				texturedCubeCount = std::stoi(stringSplit[1]);

				GameObjectManager::getInstance()->setTexturedCubeCount(texturedCubeCount);
				index++;
			}
		}
	}


}
