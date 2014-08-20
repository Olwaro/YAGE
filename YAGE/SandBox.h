#pragma once
#include <SDL.h>
#include "GameState.h"
#include "InputObserverInterface.h"
#include "KeyString.h"
#include "ActionQueue.h"

class SandBox : public GameState, public InputObserverInterface
{
	SDL_Rect rect;
	std::string id;
	std::vector<KeyString> key_strings;
	ActionQueue* delayed_actions;

public:
	SandBox();
	virtual ~SandBox();

	virtual void update();
	virtual void render();
	virtual bool on_enter();
	virtual bool on_exit();
	virtual std::string get_id() const;

	virtual void on_notify(SDL_Event*);
};

