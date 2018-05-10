#include "AmoObject.h"

AmoObject::AmoObject()
{
	rect.x = 0;
	rect.y = 0;
	x_val = 0;
	y_val = 0;
	is_move = false;
	amo_type = NONE;
}

AmoObject::~AmoObject() {}

void AmoObject::HandleInputAction(SDL_Event events)
{

}

void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
	rect.x += x_val;
	if (rect.x > x_border)
		is_move = false;
}

void AmoObject::HandleThreatAmo()
{
	rect.x -= 8;
	if (rect.x < 0)
	{
		is_move = false;
	}
}