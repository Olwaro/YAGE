#include "InputHandler.h"
#include "Debug.h"

void InputHandler::update_keys(SDL_Event* event, int ms)
{
	if (event->type == SDL_KEYDOWN && !event->key.repeat)
	{
		key_states[event->key.keysym.sym] = { true, ms };
	}
	else if (event->type == SDL_KEYUP)
	{
		auto target = key_states.find(event->key.keysym.sym);
		if (target != key_states.end())
		{
			target->second.pressed = false;
			target->second.frame = ms;
		}
	}

	notify(event, INPUT_KEYBOARD);
}

void InputHandler::force_key(int key, bool state, int ms)
{
	auto target = key_states.find(key);
	if (target != key_states.end())
	{
		target->second.pressed = state;
		target->second.frame = ms;
	}
	else
	{
		key_states[key] = { state, ms };
	}
}

bool InputHandler::is_key_pressed(int key, int& ms)
{
	auto target = key_states.find(key);
	if (target != key_states.end())
	{
		ms = target->second.frame;
		return target->second.pressed;
	}
	else
	{
		ms = 0;
		return false;
	}
}

void InputHandler::register_observer(InputObserverInterface* obs, Input what)
{
	switch (what)
	{
	case INPUT_KEYBOARD:
		keyboard_observers.push_back(obs);
		break;
	case INPUT_JOYSTICK:
		joystick_observers.push_back(obs);
		break;
	case INPUT_MOUSE:
		mouse_observers.push_back(obs);
		break;
	case INPUT_ANY:
		keyboard_observers.push_back(obs);
		joystick_observers.push_back(obs);
		mouse_observers.push_back(obs);
		break;
	default:
		Debug::warning("Trying to register observer for unknown category");
		break;
	}
}

void InputHandler::notify(SDL_Event* ev, Input what)
{
	switch (what)
	{
	case INPUT_KEYBOARD:
		for (auto obs : keyboard_observers)
		{
			obs->on_notify(ev);
		}
		break;
	case INPUT_JOYSTICK:
		for (auto obs : joystick_observers)
		{
			obs->on_notify(ev);
		}
		break;
	case INPUT_MOUSE:
		for (auto obs : mouse_observers)
		{
			obs->on_notify(ev);
		}
		break;
	default:
		break;
	}
}