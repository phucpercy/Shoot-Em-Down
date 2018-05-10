#include "MainObject.h"

MainObject::MainObject()
{
	rect.x = 0;
	rect.y = 0;
	rect.w = WIDTH_MAIN_OBJECT;
	rect.h = HEIGHT_MAIN_OBJECT;
	x_val = 0;
	y_val = 0;
}

void MainObject::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_w || events.key.keysym.sym == SDLK_UP)
			y_val -= HEIGHT_MAIN_OBJECT / 7;
		else if (events.key.keysym.sym == SDLK_s || events.key.keysym.sym == SDLK_DOWN)
			y_val += HEIGHT_MAIN_OBJECT / 7;
		else if (events.key.keysym.sym == SDLK_d || events.key.keysym.sym == SDLK_RIGHT)
			x_val += WIDTH_MAIN_OBJECT / 7;
		else if (events.key.keysym.sym == SDLK_a || events.key.keysym.sym == SDLK_LEFT)
			x_val -= WIDTH_MAIN_OBJECT / 7;
	}
	else if (events.type == SDL_KEYUP)
	{
		if (events.key.keysym.sym == SDLK_w || events.key.keysym.sym == SDLK_UP)
			y_val += HEIGHT_MAIN_OBJECT / 7;
		else if (events.key.keysym.sym == SDLK_s || events.key.keysym.sym == SDLK_DOWN)
			y_val -= HEIGHT_MAIN_OBJECT / 7;
		else if (events.key.keysym.sym == SDLK_d || events.key.keysym.sym == SDLK_RIGHT)
			x_val -= WIDTH_MAIN_OBJECT / 7;
		else if (events.key.keysym.sym == SDLK_a || events.key.keysym.sym == SDLK_LEFT)
			x_val += WIDTH_MAIN_OBJECT / 7;
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo = new AmoObject();
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(WIDTH_ROCKET, HEIGHT_ROCKET);
			p_amo->LoadImg("red_plane_rocket.png");
			p_amo->setType(AmoObject::ROCKET);
			p_amo->SetRect(this->rect.x-80 + this->rect.w-10, this->rect.y + this->rect.h*0.8);
			p_amo->set_is_move(true);
			p_amo->set_x_val(20);

			p_amo_list.push_back(p_amo);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_amo->SetWidthHeight(WIDTH_BULLET, HEIGHT_BULLET);
			p_amo->LoadImg("red_plane_bullet.png");
			p_amo->setType(AmoObject::BULLET);
			p_amo->SetRect(this->rect.x-40 + this->rect.w-10, this->rect.y + this->rect.h*0.6);
			p_amo->set_is_move(true);
			p_amo->set_x_val(20);

			p_amo_list.push_back(p_amo);
		}
	}
}

void MainObject::HandleMove()
{
	rect.x += x_val;
	if (rect.x < 0 || rect.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
	{
		rect.x -= x_val;
	}

	rect.y += y_val;
	if (rect.y < 0 || rect.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 100)
	{
		rect.y -= y_val;
	}
}

void MainObject::RemoveAmo(const int& idx)
{
	for (int i = 0; i < p_amo_list.size(); ++i)
	{
		if (idx < p_amo_list.size())
		{
			AmoObject* p_amo = p_amo_list.at(idx);
			p_amo_list.erase(p_amo_list.begin() + idx);
			if (p_amo)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
	}
}