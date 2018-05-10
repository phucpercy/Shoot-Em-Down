#include "BaseObject.h"

BaseObject::BaseObject()
{
	rect.x = 0;
	rect.y = 0;
	p_object = NULL;
}

BaseObject::~BaseObject()
{
	if (p_object != NULL)
	{
		SDL_FreeSurface(p_object);
	}
}

bool BaseObject::LoadImg(const char* file_name)
{
	p_object = SDLCommonFunc::LoadImageA(file_name);
	if (p_object == NULL)
		return false;
	return true;
}

void BaseObject::Display(SDL_Surface* des)
{
	if (p_object != NULL)
	{
		SDLCommonFunc::ApplySurface(p_object, des, rect.x, rect.y);
	}
}