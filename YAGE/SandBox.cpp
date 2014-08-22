#include "SandBox.h"
#include "Game.h"
#include "InputHandler.h"
#include "AssetManager.h"
#include "Drawing.h"
#include "String.h"
#include "Debug.h"

SandBox::SandBox()
{
	id = "SANDBOX";
}


SandBox::~SandBox()
{
}

void SandBox::update()
{
	int ms = SDL_GetTicks();
	int VMIN = 1;
	int VMAX = 6;

	InputHandler* hdl = Game::get_instance()->inputs;
	int since = 0;
	if (hdl->is_key_pressed(SDLK_DOWN, since))
	{
		int v = ((float)(VMAX - VMIN) / 2000) * (ms - since) + VMIN;
		if (v > VMAX) v = VMAX;
		rect.y += v;
		aspr->move_by(0, v);
	}
	if (hdl->is_key_pressed(SDLK_UP, since))
	{
		rect.y -= 4;
		aspr->move_by(0, -4);
	}
	if (hdl->is_key_pressed(SDLK_RIGHT, since))
	{
		rect.x += 4;
		aspr->move_by(4, 0);
	}
	if (hdl->is_key_pressed(SDLK_LEFT, since))
	{
		rect.x -= 4;
		aspr->move_by(-4, 0);
	}

	while (delayed_actions->size() > 0)
	{
		(*(delayed_actions->front()))();
		delayed_actions->pop_front();
	}

	aspr->update(ms);
}

void SandBox::render()
{
	auto rndr = Game::get_instance()->renderer;
	SDL_SetRenderDrawColor(rndr, 255, 0, 0, 0);
	//SDL_RenderFillRect(Game::get_instance()->renderer, &rect);

	//Drawing::draw_full_texture(rndr, Game::get_instance()->assets->get_texture("SDL"), 100, 100);
	aspr->draw(rndr);
}

bool SandBox::on_enter()
{
	rect.h = 20;
	rect.w = 60;
	rect.x = 30;
	rect.y = 30;

	delayed_actions = new ActionQueue(256);

	key_strings.push_back(KeyString({ SDLK_l, SDLK_o, SDLK_l }, -1, [this]() {
		rect.h *= 4;
	}));

	Game::get_instance()->inputs->register_observer(this, INPUT_KEYBOARD);
	Game::get_instance()->inputs->register_observer(this, INPUT_MOUSE);

	Game::get_instance()->assets->load_texture("SDL_logo.png", "SDL");
	Game::get_instance()->assets->load_texture("ani.png", "ani");
	Game::get_instance()->assets->load_animation("animation_tim.xml", "tim");

	aspr = new AnimatedSprite(0, 0, 61, 70);
	aspr->set_animation(Game::get_instance()->assets->get_animation("tim"));

	return true;
}

bool SandBox::on_exit()
{
	delete[] delayed_actions;

	return true;
}

std::string SandBox::get_id() const
{
	return id;
}

void SandBox::on_notify(SDL_Event* ev)
{
	int ms = SDL_GetTicks();
	if (ev->type == SDL_KEYDOWN)
	{
		for (auto& str : key_strings)
		{
			if (str.step(ev->key.keysym.sym, ms))
			{
				delayed_actions->push_back(str.get_callback());
			}
		}
	}

	if (ev->type == SDL_MOUSEWHEEL)
	{
		aspr->set_frame_time(aspr->get_frame_time() + ev->wheel.y);
		Debug::warning(std::to_string(aspr->get_frame_time()));
	}
}
