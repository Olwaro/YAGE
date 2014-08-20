#include "Drawing.h"

void Drawing::draw_full_texture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
	SDL_Rect r_source {0, 0};
	SDL_Rect r_target;
	SDL_QueryTexture(texture, NULL, NULL, &(r_source.w), &(r_source.h));
	r_target.x = x;
	r_target.y = y;
	r_target.w = r_source.w;
	r_target.h = r_source.h;

	SDL_RenderCopy(renderer, texture, &r_source, &r_target);
}