#pragma once

#include <SDL.h>
#include <vector>

#include "Animation.h"

class AnimatedSprite
{
	Animation* _animation = nullptr;

	double _x;
	double _y;
	int _width;
	int _height;
	double _rotation = 0;

	int _current_frame = 0;
	int _current_time = 0;
	int _frame_time = 15;

public:
	AnimatedSprite(double x, double y, int w, int h);
	~AnimatedSprite();

	void update(int time);
	void draw(SDL_Renderer* renderer);

	void move_by(int dx, int dy);
	void rotate(double angle);

	void set_animation(Animation* animation);
	void set_frame_time(int t);
	int get_frame_time();
};

