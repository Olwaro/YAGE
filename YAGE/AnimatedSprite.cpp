#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(double x, double y, int w, int h) :
	_x(x),
	_y(y),
	_width(w),
	_height(h)
{
}


AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::set_animation(Animation* animation)
{
	_current_frame = 0;
	_animation = animation;
}

void AnimatedSprite::update(int time)
{
	if (_animation)
	{
		if (time - _current_time > _frame_time)
		{
			_current_time = time - ((time - _current_time) - _frame_time);
			_current_frame = (_current_frame + 1) % _animation->get_size(); // put size in local class variable ?
		}
	}
}

void AnimatedSprite::draw(SDL_Renderer* renderer)
{
	if (_animation)
	{
		SDL_Rect* sr = _animation->get_frame(_current_frame);
		SDL_Rect tr = { _x, _y, _width, _height };

		SDL_RenderCopyEx(renderer, _animation->get_texture(), sr, &tr, _rotation, NULL, SDL_FLIP_NONE);
	}
}

void AnimatedSprite::move_by(int dx, int dy)
{
	_x += dx;
	_y += dy;
}

void AnimatedSprite::rotate(double angle)
{
	_rotation += angle;
}

void AnimatedSprite::set_frame_time(int t)
{
	if (t < 0)
		t = 0;
	_frame_time = t;
}

int AnimatedSprite::get_frame_time()
{
	return _frame_time;
}