#pragma once
#include <string>

class SceneWriter
{
public:
	SceneWriter();
	~SceneWriter();

	void writeToFile(std::string filePath);
};

