#pragma once

#include <string>

class CGhostLoader
{
public:
	CGhostLoader();

	bool LoadFromMemory(unsigned char* data, unsigned int size);
	bool LoadFromFile(const std::string& fileName);
};
