#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "BaseObject.h"

const int EXP_WIDTH = 165;
const int EXT_HEIGHT = 165;

class Explosion : public BaseObject
{
private:
	int frame;
	SDL_Rect clip[4];

public:
	Explosion();

	void set_frame(const int& fr) { frame = fr; }
	void DisplayExplosion(SDL_Surface* des);
};

#endif
