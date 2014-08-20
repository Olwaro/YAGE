#include "CachedFont.h"
#include "Debug.h"
#include "String.h"

const std::string CachedFont::CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-+=!?,:";

CachedFont::CachedFont()
{
}

CachedFont::~CachedFont()
{
}

void CachedFont::draw_text(const std::string& text, int x, int y, SDL_Renderer* renderer)
{
	SDL_Rect r = { 0, 0, f_width, f_height };
	SDL_Rect r_t = { x, y, f_width, f_height };


	// WORK IN PROGRESS 
	for (int i = 0; i < text.length(); ++i)
	{
		// get index of text[i] in CHARS -> idx
		// r.x = idx * f_width
		// blit r, r_t
		// x += f_width
	}
}


CachedFont* CachedFont::Make(const std::string& font_name, int size, SDL_Renderer* renderer)
{
	TTF_Font* f = TTF_OpenFont(font_name.c_str(), size);
	Debug::check_assert(f != NULL, String::concat("Unable to load font ", font_name));

	return CachedFont::Make(f, renderer);
}

CachedFont* CachedFont::Make(TTF_Font* font, SDL_Renderer* renderer)
{
	CachedFont* cf = new CachedFont();
	cf->font = font;
	TTF_GlyphMetrics(cf->font, 'O', NULL, NULL, NULL, NULL, &(cf->f_width));
	cf->f_height = TTF_FontHeight(cf->font);

	cf->font_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, cf->f_width * CHARS.length(), cf->f_height);
	SDL_SetRenderTarget(renderer, cf->font_texture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

	SDL_Rect r = { 0, 0, cf->f_width, cf->f_height };
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface* s;
	SDL_Texture* t;

	for (int i = 1; i < CHARS.length(); ++i)
	{
		s = TTF_RenderGlyph_Blended(cf->font, CHARS[i], white);
		t = SDL_CreateTextureFromSurface(renderer, s);

		r.x = cf->f_width * i;
		SDL_RenderCopy(renderer, t, NULL, &r);

		SDL_FreeSurface(s);
		SDL_DestroyTexture(t);
	}

	SDL_SetRenderTarget(renderer, NULL);

	return cf;
}
