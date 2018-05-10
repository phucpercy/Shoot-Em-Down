#include "ThreatsObject.h"

ThreatObject::ThreatObject()
{
	rect.x = SCREEN_WIDTH;
	rect.y = SCREEN_HEIGHT*0.5;
	rect.w = WIDTH_THREAT;
	rect.h = HEIGHT_THREAT;

	x_val = 0;
	y_val = 0;
}

ThreatObject::~ThreatObject() 
{
	if (p_amo_list.size() > 0)
	{
		for (int i = 0; i < p_amo_list.size(); ++i)
		{
			AmoObject* p_amo = p_amo_list.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
	if (p_amo)
	{
		bool res = p_amo->LoadImg("sphere.png");
		if (res)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_BULLET, HEIGHT_BULLET);
			p_amo->setType(AmoObject::BULLET);
			p_amo->SetRect(rect.x, rect.y + rect.h*0.5);
			p_amo_list.push_back(p_amo);
		}
	}
}

void ThreatObject::ThreatShoot(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_amo_list.size(); ++i)
	{
		AmoObject* p_amo = p_amo_list.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Display(des);
				p_amo->HandleThreatAmo();
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect.x, rect.y + rect.h*0.5);
			}
		}
		else
		{			
			p_amo->set_is_move(true);
			p_amo->SetRect(rect.x, rect.y + rect.h*0.5);
		}
	}
}

void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	rect.x -= x_val;
	if (rect.x < 0)
	{
		rect.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - 200)
		{
			rand_y = SCREEN_HEIGHT*0.3;
		}
		rect.y = rand_y;
	}

}

void ThreatObject::HandleInputAction(SDL_Event events)
{

}

void ThreatObject::Reset(const int& xborder)
{
	rect.x = xborder;
	rect.x = SCREEN_WIDTH;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - 200)
	{
		rand_y = SCREEN_HEIGHT*0.3;
	}
	rect.y = rand_y;
// 	for (int i = 0; i < p_amo_list.size(); ++i)
// 	{
// 		AmoObject* p_amo = p_amo_list.at(i);
// 		if (p_amo)
// 		{
// 			ResetAmo(p_amo);
// 		}
// 	}
}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect.x, rect.y + rect.h*0.5);
}