#pragma once
#include <vector>
#include "GameState.h"

class StateMachine
{
	std::vector<GameState*> states;
public:
	StateMachine();
	~StateMachine();

	void push_state(GameState* state);
	void pop_state();
	void change_state(GameState* state);

	void update();
	void render();
};

