#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include "Animation.h"

class AssetManager
{
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Animation*> animations;

public:
	AssetManager();
	~AssetManager();

	SDL_Texture* get_texture(const std::string&) const;
	bool load_texture(const std::string& path, const std::string& id);

	Animation* get_animation(const std::string&) const;
	bool load_animation(const std::string& path, const std::string& id);

};

