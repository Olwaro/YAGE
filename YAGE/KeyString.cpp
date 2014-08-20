#include "KeyString.h"


KeyString::KeyString(std::vector<int> keys, int interval, Action callback) :
	keys(keys),
	interval(interval),
	callback(callback),
	last_frame(0)
{
}


KeyString::~KeyString()
{
}

bool KeyString::step(int key, int ms)
{
	bool finish = false;

	if (keys[idx] == key && (idx == 0 || interval == -1 || ms - last_frame <= interval))
	{
		idx++;
	}
	else
	{
		reset();
	}

	if (idx >= keys.size())
	{
		reset();
		finish = true;
	}

	last_frame = ms;
	return finish;
}

void KeyString::reset()
{
	idx = 0;
}

inline Action* get_callback();