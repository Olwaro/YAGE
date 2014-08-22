#include "AssetManager.h"

#include <SDL_image.h>
#include "Game.h"
#include "Debug.h"
#include "String.h"
#include "xml/pugixml.hpp"

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
	auto it = textures.find(id);
	if (it == textures.end()) {
		Debug::warning(String::concat("Unable to load texture : ", id));
		return SDL_CreateTexture(Game::get_instance()->renderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STATIC, 10, 10);
	}
	else {
		return it->second;
	}
}

bool AssetManager::load_animation(const std::string& path, const std::string& id)
{
	pugi::xml_document doc;
	auto result = doc.load_file(path.c_str());
	auto root = doc.first_child();
	
	std::string texture_id;
	Animation* anim = new Animation();

	if (result)
	{
		texture_id = root.child("texture").attribute("id").as_string();
		anim->set_texture(this->get_texture(texture_id));

		for (auto node : root.child("frames").children())
		{
			anim->add_frame({ 
				node.attribute("x").as_int(0),
				node.attribute("y").as_int(0),
				node.attribute("w").as_int(10), 
				node.attribute("h").as_int(10) });
		}

		animations[id] = anim;
	}
	else
	{
		Debug::warning(String::concat("pugixml error -> ", result.description()));
		return false;
	}

	return true;
}

Animation* AssetManager::get_animation(const std::string& id) const
{
	auto it = animations.find(id);
	if (it == animations.end()) {
		Debug::warning(String::concat("Unable to load animation : ", id));
		return nullptr;
	}
	else {
		return it->second;
	}
}