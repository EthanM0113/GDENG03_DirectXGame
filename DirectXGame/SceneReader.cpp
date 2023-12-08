#include "SceneReader.h"
#include <iostream>
#include <fstream>

#include "ActionHistory.h"
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

	if(filePath.find(".level") != std::string::npos)
	{
		std::string objectName;
		PrimitiveType objectType;
		Vector3D position;
		Vector3D rotation;
		Vector3D scale;
		std::string materialPath;
		std::string readLine;

		// Rigidbody
		bool hasRigidbody = false;
		float mass = 0.f;
		bool isGravity = true;

		int cubeCount;
		int planeCount;
		int physicsCubeCount;
		int physicsPlaneCount;
		int texturedCubeCount;

		bool finishedGameObjects = false;

		// Delete all game objects
		GameObjectManager::getInstance()->deleteAllObjects();

		// Clear action history
		ActionHistory::getInstance()->clear();

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
					// If object is not textured cube AND has NO rigidbody
					if (objectType != TEXTURED_CUBE && !hasRigidbody)
						GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, hasRigidbody, mass, isGravity);

					finishedGameObjects = true;
				}
				else if (specialCheckCount)
				{
					if (index == 6 && readLine.find("CubeCount: ") != std::string::npos)
					{
						finishedGameObjects = true;
						index = 5;
						specialCheckCount = false;
						hasRigidbody = false;
					}
					else if (index == 8 && hasRigidbody)
					{
						if (readLine.find("CubeCount: ") != std::string::npos)
						{
							finishedGameObjects = true;
							index = 5;
							specialCheckCount = false;
							hasRigidbody = false;
						}
						else
						{
							index = 0;
							hasRigidbody = false;
							specialCheckCount = false;
						}
					}
					else if (index == 6 && hasRigidbody)
					{
						// Get mass
						mass = std::stof(readLine);
						index++;
					}
					else if (index == 7 && hasRigidbody)
					{
						// Get is gravity enabled
						if (readLine.find("GravityEnabled") != std::string::npos)
						{
							isGravity = true;
						}
						else if (readLine.find("GravityDisabled") != std::string::npos)
						{
							isGravity = false;
						}
						// Game object with rigidbody component
						GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, hasRigidbody, mass, isGravity);

						index++;
					}
					else
					{
						index = 0;
						hasRigidbody = false;
						specialCheckCount = false;
					}
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
					else if (readLine.find("Has Rigidbody") != std::string::npos)
					{
						hasRigidbody = true;

						// Get mass from next line
						index++;
						specialCheckCount = true;
					}
					else
					{
						// If object is not textured cube AND has NO rigidbody
						if (objectType != TEXTURED_CUBE && !hasRigidbody)
							GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, hasRigidbody, mass, isGravity);

						index = 0;
						hasRigidbody = false;
					}
				}
			}

			if (!specialCheckCount)
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
	else if(filePath.find(".unity") != std::string::npos)
	{
		std::cout << "UNITY FILE LOADED" << std::endl;

		// Reads Game Object and their transforms, names, limited rigidbody
		// Unlike .level, does not track object counts & material, assumes read only on load for unity files

		std::string objectName;
		PrimitiveType objectType = PrimitiveType::CUBE; // always assume cube even for planes
		Vector3D position;
		Vector3D rotation;
		Vector3D scale;
		std::string readLine;

		// Rigidbody
		bool hasRigidbody = false;
		float mass = 0.f;
		bool isGravity = true;
		bool isKinematic = false;

		// Delete all game objects
		GameObjectManager::getInstance()->deleteAllObjects();

		// Clear action history
		ActionHistory::getInstance()->clear();

		bool insideGameObject = false;
		bool insideRigidBody = false;

		while (std::getline(sceneFile, readLine))
		{
			if(readLine.find("m_Name") != std::string::npos && !insideGameObject)
			{
				// Get Object Name
				std::vector<std::string> nameSplit = StringUtils::split(readLine, ' ');
				std::string unityName;
				unityName =  nameSplit[3]; // name
				if(nameSplit.size() == 5) // If name has number assignment
				{
					unityName.append(nameSplit[4]); // possible number
				}
				objectName = unityName;
				std::cout << "Name: " << objectName << std::endl;

				insideGameObject = true;
			}
			if(insideGameObject)
			{
				if (readLine.find("m_LocalRotation") != std::string::npos)
				{
					std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
					std::vector<std::string> rotXSplit = StringUtils::split(stringSplit[4], ','); // x value
					std::vector<std::string> rotYSplit = StringUtils::split(stringSplit[6], ','); // y value
					std::vector<std::string> rotZSplit = StringUtils::split(stringSplit[8], ','); // z value

					// Assign to Vector 3D
					rotation = new Vector3D(std::stof(rotXSplit[0]), std::stof(rotYSplit[0]), std::stof(rotZSplit[0]));
					std::cout << "Rotation: " << rotation.getValues().x << " " << rotation.getValues().y << " " << rotation.getValues().z << std::endl;
				}
				else if (readLine.find("m_LocalPosition") != std::string::npos)
				{
					std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
					std::vector<std::string> posXSplit = StringUtils::split(stringSplit[4], ','); // x value
					std::vector<std::string> posYSplit = StringUtils::split(stringSplit[6], ','); // y value
					std::vector<std::string> posZSplit = StringUtils::split(stringSplit[8], '}'); // z value

					// Assign to Vector 3D
					position = new Vector3D(std::stof(posXSplit[0]), std::stof(posYSplit[0]), std::stof(posZSplit[0]));
					std::cout << "Position: " << position.getValues().x << " " << position.getValues().y << " " << position.getValues().z << std::endl;

				}
				else if (readLine.find("m_LocalScale") != std::string::npos)
				{
					std::vector<std::string> stringSplit = StringUtils::split(readLine, ' ');
					std::vector<std::string> scaleXSplit = StringUtils::split(stringSplit[4], ','); // x value
					std::vector<std::string> scaleYSplit = StringUtils::split(stringSplit[6], ','); // y value
					std::vector<std::string> scaleZSplit = StringUtils::split(stringSplit[8], '}'); // z value

					// Assign to Vector 3D
					scale = new Vector3D(std::stof(scaleXSplit[0]), std::stof(scaleYSplit[0]), std::stof(scaleZSplit[0]));
					std::cout << "Scale: " << scale.getValues().x << " " << scale.getValues().y << " " << scale.getValues().z << std::endl;
				}

				
				// If has Rigidbody, attach physics component, otherwise move on to next object
				if (readLine.find("Rigidbody") != std::string::npos)
				{
					std::cout << "HAS RIGIDBODY" << std::endl;
					hasRigidbody = true;
					insideRigidBody = true;
				}
				else if(insideRigidBody)
				{
					if (readLine.find("m_Mass") != std::string::npos)
					{
						// Get Mass
						std::vector<std::string> massSplit = StringUtils::split(readLine, ' ');
						mass = std::stof(massSplit[3]); // mass
						std::cout << "Mass: " << mass << std::endl;
					}
					else if (readLine.find("m_UseGravity") != std::string::npos)
					{
						// Get Gravity
						std::vector<std::string> gravitySplit = StringUtils::split(readLine, ' ');
						int value = std::stoi(gravitySplit[3]);

						if(value == 0)
						{
							isGravity = false;
						}
						else if (value == 1)
						{
							isGravity = true;
						}

						std::cout << "Is Gravity Enabled: " << isGravity << std::endl;
					}
					else if (readLine.find("m_IsKinematic") != std::string::npos)
					{
						// Get Kinematic
						std::vector<std::string> kinematicSplit = StringUtils::split(readLine, ' ');
						int value = std::stoi(kinematicSplit[3]);

						if (value == 0)
						{
							isKinematic = false;
						}
						else if (value == 1)
						{
							isKinematic = true;
						}
						std::cout << "Is Kinematic Enabled: " << isKinematic << std::endl;

						// Create Object
						GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, hasRigidbody, mass, isGravity, isKinematic);

						// Proceed to next object
						hasRigidbody = false;
						insideRigidBody = false;
						insideGameObject = false;
					}
				}
				else if (readLine.find("m_Component") != std::string::npos || readLine.find("SceneRoots") != std::string::npos) // m_Component is unique only to GameObject section, ScenRoots is at the end of the file
				{
					std::cout << "CREATE GAME OBJECT" << std::endl;

					// Create Object
					GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, hasRigidbody, mass, isGravity);

					// Proceed to next object
					insideGameObject = false;
				}

			}
		}
	}










	// Backup While Loop
	/*
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
			else if (index == 6 && specialCheckCount)
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

		if (!specialCheckCount)
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
	*/
}
