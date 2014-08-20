#include <iostream>
#include <SDL.h>
#include "Debug.h"


void Debug::warning(const std::string& message)
{
	std::cerr << "Warning: " << message << std::endl;
}

void Debug::error(const std::string& message)
{
	std::cerr << "Error: " << message << std::endl;
}

void Debug::die(const std::string& message)
{
	std::cerr << "Fatal : " << message << std::endl;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal error", message.c_str(), NULL);
	std::abort();
}

void Debug::check_assert(bool assertion, const std::string& message)
{
	if (!assertion)
	{
		die(message);
	}
}