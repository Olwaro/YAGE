#pragma once
#include <map>
#include <vector>
#include <SDL.h>
#include "InputObserverInterface.h"

struct Keystate {
	bool pressed;
	int frame;
};

enum Input
{
	INPUT_KEYBOARD,
	INPUT_JOYSTICK,
	INPUT_MOUSE,
	INPUT_ANY
};

class InputHandler
{
	std::map<int, Keystate> key_states;
	std::vector<InputObserverInterface*> keyboard_observers;
	std::vector<InputObserverInterface*> joystick_observers;
	std::vector<InputObserverInterface*> mouse_observers;

public:

	// Keyboard handling
	void update_keys(SDL_Event* event, int ms);
	void force_key(int key, bool state, int ms);
	bool is_key_pressed(int key, int& ms);

	// Mouse handling
	void handle_mouse(SDL_Event* event, int ms);

	// Observer pattern
	void register_observer(InputObserverInterface* obs, Input what);
	void notify(SDL_Event* ev,Input what);

};

