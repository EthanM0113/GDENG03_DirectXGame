#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class AResource;
class AResourceManager
{
public:
	//typedef std::wstring String;
	typedef std::unordered_map<std::wstring, AResource*> HashTable;

	//Resource* createResourceFromFile(const wchar_t* filePath);

protected:
	AResourceManager();
	~AResourceManager();

	HashTable resourceMap;

private:
	AResourceManager(AResourceManager const&) {};             // copy constructor is private
	AResourceManager& operator=(AResourceManager const&) {};  // assignment operator is private*/
};