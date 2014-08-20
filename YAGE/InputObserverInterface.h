#pragma once
#include <SDL.h>

class InputObserverInterface
{
public: 
	virtual ~InputObserverInterface() {};
	virtual void on_notify(SDL_Event*) = 0;
};