#pragma once
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

class InputHandler;
class StateMachine;
class AssetManager;

class Game
{
	Game();

	SDL_Window* main_window = nullptr;
	char* mw_title;
	int current_fps;

	// Methods
	void handle_events(SDL_Event* event);
	void update();
	void render();
	void clean();

public:
	InputHandler* inputs;
	StateMachine* state_machine;
	AssetManager* assets;
	SDL_Renderer* renderer;
	SDL_Surface* mw_surface;
	int mw_width;
	int mw_height;
	bool running = false;

	// Methods
	int init(char* title, int width, int height);
	void start_loop();
	static Game* get_instance();
	static Game* I();

	//todo move
	TTF_Font* debug_font;
	SDL_Surface *debug_txt;
	int last_update = 0;
	SDL_Rect debug_target;
};

