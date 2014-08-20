#include <iostream>
#include "Game.h"

#include "Debug.h"

int main(int argc, char** args)
{

	Game* aze = Game::get_instance();
	if (!aze->init("Test", 1280, 720))
	{
		aze->start_loop();
	}
	else
	{
		std::cerr << "Closing" << std::endl;
		return -1;
	}

	return 0;
}