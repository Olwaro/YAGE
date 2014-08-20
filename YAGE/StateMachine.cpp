#include <iostream>
#include "StateMachine.h"
#include "Debug.h"

StateMachine::StateMachine()
{

}

StateMachine::~StateMachine()
{
	for (auto state : states)
	{
		delete state;
	}
}

void StateMachine::push_state(GameState* state)
{
	states.push_back(state);
	states.back()->on_enter();
}

void StateMachine::pop_state()
{
	if (!states.empty())
	{
		if (states.back()->on_exit())
		{
			delete states.back();
			states.pop_back();
		}
		else
		{
			Debug::warning("Current state cannot be poped now");
		}
	}
	else
	{
		Debug::warning("Trying to pop on empty state stack");
	}
}

void StateMachine::change_state(GameState* state)
{
	if (!states.empty())
	{
		if (states.back()->get_id() == state->get_id())
		{
			return; // do nothing
		}

		pop_state();
	}

	push_state(state);
}

void StateMachine::update()
{
	if (!states.empty())
	{
		states.back()->update();
	}
}

void StateMachine::render()
{
	if (!states.empty())
	{
		states.back()->render();
	}
}