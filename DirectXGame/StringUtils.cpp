#include "StringUtils.h"
#include <sstream>

std::vector<std::string> StringUtils::split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}
