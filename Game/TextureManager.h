#pragma once
#include <string>
#include <map>
#include "graphics.h"

using std::string;
using std::map;

class TextureManager
{
private:
	map<string, unsigned int> look_up;
public:
	TextureManager();
	void InitializeTextures();
	void StartTexture(string name);
	void EndTexture();
};

