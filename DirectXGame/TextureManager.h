#pragma once
#include "AResourceManager.h"

class Texture;
class TextureManager : public AResourceManager
{
public:
	static void initialize();
	static void destroy();
	static TextureManager* getInstance();
	Texture* createTextureFromFile(const wchar_t* filePath);

private:
	static TextureManager* sharedInstance;

	TextureManager();
	~TextureManager();
	AResource* convertToResource(const wchar_t* filePath);

};