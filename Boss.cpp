#include "Boss.h"

Boss::Boss()
{
	rect.x = SCREEN_WIDTH;
	rect.y = (SCREEN_HEIGHT - 200) / 2;
	rect.w = WIDTH_BOSS;
	rect.h = HEIGHT_BOSS;
	x_val = 2;
	y_val = 2;
	boss_hp = 100;
}

Boss::~Boss()
{
	if (p_amo_list.size() > 0)
	{
		for (int i = 0; i < p_amo_list.size(); ++i)
		{
			AmoObject* p_amo = p_amo_list.at(i);
			if (p_amo != NULL)
			{
				delete(p_amo);
				p_amo = NULL;
			}
		}
		p_amo_list.clear();
	}
}

void Boss::BossMoveOut()
{
	if (rect.x >= SCREEN_WIDTH - WIDTH_BOSS)
	{
		rect.x -= 1;
	}
}

void Boss::HandleBossMove(const int& x_desPos, const int& y_desPos)
{
	if (rect.x >= x_desPos && rect.x < (SCREEN_WIDTH-WIDTH_BOSS))
	{
		rect.x -= x_val;
	}
	else if (rect.x < x_desPos && rect.x >= SCREEN_WIDTH/2)
	{
		rect.x += x_val;
	}
	if (rect.y >= y_desPos && rect.y <= SCREEN_HEIGHT-200)
	{
		rect.y -= y_val;
	}
	else if (rect.y < y_desPos && rect.y >= 0)
	{
		rect.y += y_val;
	}
}

void Boss::InitAmo(AmoObject* p_amo)
{
	if (p_amo)
	{
		bool res = p_amo->LoadImg("purple_plane_bullet.png");
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

void Boss::BossShoot(SDL_Surface* des, const int& x_limit, const int& y_limit)
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