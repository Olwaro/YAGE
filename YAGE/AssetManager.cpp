#include "AssetManager.h"

#include <SDL_image.h>
#include "Game.h"
#include "Debug.h"
#include "String.h"

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

bool AssetManager::load_texture(const std::string& path, const std::string& id)
{
	SDL_Surface* tmp_surface = IMG_Load(path.c_str());
	if (tmp_surface == NULL)
	{
		Debug::warning(String::concat("Connot load asset : ", path));
		return false;
	}
	else
	{
		textures[id] = SDL_CreateTextureFromSurface(Game::get_instance()->renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
	}
	return true;
}

SDL_Texture* AssetManager::get_texture(const std::string& id) const
{
	if (textures.empty())
	{
		return SDL_CreateTexture(Game::get_instance()->renderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STATIC, 10, 10);
	}

	auto it = textures.find(id);
	if (it == textures.end()) {
		return SDL_CreateTexture(Game::get_instance()->renderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STATIC, 10, 10);
	}
	else {
		return it->second;
	}
}