#pragma once

#include <map>
#include <string>
#include "SDL.h"

class AssetManager
{
	std::map<std::string, SDL_Texture*> textures;

public:
	AssetManager();
	~AssetManager();

	SDL_Texture* get_texture(const std::string&) const;
	bool load_texture(const std::string& path, const std::string& id);
};

