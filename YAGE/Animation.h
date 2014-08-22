#pragma once

#include <SDL.h>
#include <vector>
#include <initializer_list>

class Animation
{
	std::vector<SDL_Rect> _frames;
	SDL_Texture* _texture = nullptr;

public:
	Animation();
	~Animation();

	void set_frames(std::initializer_list<SDL_Rect> frames);
	void add_frame(SDL_Rect frame);
	void set_texture(SDL_Texture* texture);
	SDL_Texture* get_texture() const;
	int get_size() const;
	SDL_Rect* get_frame(int n);
};

