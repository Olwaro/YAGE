#include "Game.h"

#include <cstdio>

#include "InputHandler.h"
#include "StateMachine.h"
#include "SandBox.h"
#include "AssetManager.h"
#include "Debug.h"
#include "String.h"

Game::Game()
{
	
}

Game* Game::get_instance()
{
	static Game* instance = new Game();
	return instance;
}

Game* Game::I()
{
	return get_instance();
}

int Game::init(char* title, int width, int height)
{
	mw_width = width;
	mw_height = height;
	mw_title = title;

	// Let SDL do its init properly
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// Create the main window
	main_window = SDL_CreateWindow(
		mw_title,					// window title
		SDL_WINDOWPOS_CENTERED,		// initial x position
		SDL_WINDOWPOS_CENTERED,		// initial y position
		mw_width,					// width, in pixels
		mw_height,					// height, in pixels
		SDL_WINDOW_SHOWN			// flags
		);

	// Check that the window was successfully made
	Debug::check_assert(main_window != NULL, String::concat("Could not create window: ", SDL_GetError() ));

	//todo move to assetmanager
	debug_font = TTF_OpenFont("visitor1.ttf", 24);
	Debug::check_assert(debug_font != NULL, "Unable to load font ");

	// Initialise renderer stuff
	renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	mw_surface = SDL_GetWindowSurface(main_window);

	// Init modules
	inputs = new InputHandler();
	state_machine = new StateMachine();
	assets = new AssetManager();

	// Add first game state
	state_machine->push_state(new SandBox());

	running = true;

	return 0;
}

void Game::start_loop()
{
	int e, s;

	SDL_Event event;
	while (running)
	{

		e = SDL_GetTicks();

		// Pumping events SDL events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}

			handle_events(&event);
		}

		update();
		render();

		s = SDL_GetTicks();
		current_fps =  1000 / ((s - e) + 1);
	}

	clean();
}

void Game::handle_events(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
	{
		inputs->update_keys(event, SDL_GetTicks());
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION|| event->type == SDL_MOUSEWHEEL)
	{
		inputs->handle_mouse(event, SDL_GetTicks());
	}
}

void Game::update()
{
	state_machine->update();

	// update debug info
	if (SDL_GetTicks() - last_update > 500)
	{
		char out[5] = "    ";
		sprintf_s(out, 5, "%d", current_fps);

		debug_txt = TTF_RenderText_Solid(debug_font, out, {0, 255, 0});
		last_update = SDL_GetTicks();
		debug_target.h = debug_txt->clip_rect.h;
		debug_target.w = debug_txt->clip_rect.w;
		debug_target.x = mw_width - debug_txt->clip_rect.w;
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	state_machine->render();

	// Render debug info
	SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, debug_txt);
	SDL_RenderCopy(renderer, t, &(debug_txt->clip_rect), &debug_target);
	SDL_DestroyTexture(t);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(main_window);
	TTF_Quit();
	SDL_Quit();
}
