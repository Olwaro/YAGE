#include "Animation.h"


Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::set_frames(std::initializer_list<SDL_Rect> frames)
{
	_frames.clear();
	_frames.insert(_frames.end(), frames.begin(), frames.end());
}

void Animation::add_frame(SDL_Rect frame)
{
	_frames.push_back(frame);
}

void Animation::set_texture(SDL_Texture* texture)
{
	_texture = texture;
}

SDL_Texture* Animation::get_texture() const
{
	return _texture;
}

int Animation::get_size() const
{
	return _frames.size();
}

SDL_Rect* Animation::get_frame(int n)
{
	return &_frames[n];
}