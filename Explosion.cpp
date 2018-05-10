#include "Explosion.h"

Explosion::Explosion()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = EXP_WIDTH;
	clip[0].h = EXT_HEIGHT;

	clip[1].x = EXP_WIDTH;
	clip[1].y = 0;
	clip[1].w = EXP_WIDTH;
	clip[1].h = EXT_HEIGHT;

	clip[2].x = 2*EXP_WIDTH;
	clip[2].y = 0;
	clip[2].w = EXP_WIDTH;
	clip[2].h = EXT_HEIGHT;

	clip[3].x = 3*EXP_WIDTH;
	clip[3].y = 0;
	clip[3].w = EXP_WIDTH;
	clip[3].h = EXT_HEIGHT;
}

void Explosion::DisplayExplosion(SDL_Surface* des)
{
	if (frame >= 4)
	{
		frame = 0;
	}

	SDLCommonFunc::ApplyClip(this->p_object, des, &clip[frame], rect.x, rect.y);
}