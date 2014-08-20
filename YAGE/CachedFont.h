#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class CachedFont
{
	TTF_Font* font;
	SDL_Texture* font_texture;

	int f_width;
	int f_height;

	CachedFont();

public:
	~CachedFont();

	void draw_text(const std::string& text, int x, int y, SDL_Renderer* renderer);

	static CachedFont* Make(const std::string& font_name, int size, SDL_Renderer* renderer);
	static CachedFont* Make(TTF_Font* font, SDL_Renderer* renderer);
	static const std::string CHARS;
};

