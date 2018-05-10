#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	bool LoadImg(const char* file_name);
	void Display(SDL_Surface* des);

	void SetRect(const int& x, const int& y)
	{
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect GetRect() const
	{
		return rect;
	}
	SDL_Surface* GetObject()
	{
		return p_object;
	}

protected:
	SDL_Rect rect;
	SDL_Surface* p_object;
};

#endif
