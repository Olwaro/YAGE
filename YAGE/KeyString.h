#pragma once
#include <vector>
#include "ActionQueue.h"

class KeyString
{
	Action callback;
	std::vector<int> keys;
	int idx = 0;
	int interval = 0;
	int last_frame = 0;

public:
	KeyString(std::vector<int> keys, int interval, Action callback);
	~KeyString();

	bool step(int key, int ms);
	void reset();

	inline Action* get_callback()
	{
		return &callback;
	}
};

