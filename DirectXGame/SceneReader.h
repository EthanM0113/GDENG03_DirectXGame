#pragma once
#include <string>

class SceneReader
{
public:
	SceneReader();
	~SceneReader();

	void loadFromFile(std::string filePath);
};

