#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "Boss.h"
using namespace SDLCommonFunc;

MainObject plane;
ThreatObject* p_threats = new ThreatObject[NUM_THREAT];
Boss* p_boss = new Boss();
Explosion explosion_main;
Mix_Music* music_background = NULL;
int score = 0;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;

	TTF_Init();

	SDL_WM_SetCaption("Shoot 'Em Down", "Shoot 'Em Down");
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
		return false;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;

	return true;
}

bool ShowMenu()
{
	int x_mouse, y_mouse;
	bool play = true;
	SDL_Surface* button = NULL;
	SDL_Surface* red_plane = LoadImage("game_menu_red_plane.png");
	g_menu = LoadImage("game_menu.png");
	ApplySurface(g_menu, g_screen, 0, 0);

	while (play == true)
	{
		SDL_PollEvent(&g_event);
		if ((g_event.type == SDL_MOUSEMOTION || g_event.type == SDL_MOUSEBUTTONDOWN) && g_event.type != SDL_QUIT)
		{
			x_mouse = g_event.motion.x;
			y_mouse = g_event.motion.y;
			if (715 <= x_mouse && x_mouse <= 901 && 295 <= y_mouse && y_mouse <= 346)
			{
				button = LoadImage("game_menu_start.png");
				ApplySurface(button, g_screen, 715, 295);
				ApplySurface(red_plane, g_screen, 650, 295);
				if (g_event.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_FreeSurface(button);
					return true;
				}
			}
			else if (715 <= x_mouse && x_mouse <= 900 && 370 <= y_mouse && y_mouse <= 421)
			{
				button = LoadImage("game_menu_exit.png");
				ApplySurface(button, g_screen, 715, 370);
				ApplySurface(red_plane, g_screen, 650, 370);
				if (g_event.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_FreeSurface(button);
					return false;
				}
			}
			else
			{
				ApplySurface(g_menu, g_screen, 0, 0);
			}
		}
		if (SDL_Flip(g_screen) == -1)
			return false;
	}
}

void InitCharacterToGame()
{
	//Init player main object
	plane.SetRect(100, 200);
	if (!(plane.LoadImg("red_plane.png")))
		return;
	plane.Display(g_screen);

	//Init Threat
	for (int i = 0; i < NUM_THREAT; ++i)
	{
		ThreatObject* p_threat = p_threats + i;
		p_threat->LoadImg("mini_theat_plane.png");
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - 200)
		{
			rand_y = SCREEN_HEIGHT*0.3;
		}
		p_threat->SetRect(SCREEN_WIDTH + i * 400, rand_y);
		p_threat->set_x_val(speed);

		AmoObject* p_amo = new AmoObject();
		p_threat->InitAmo(p_amo);
	}

	//Initialize Boss
	p_boss->LoadImg("purple_plane.png");
	p_boss->SetRect(SCREEN_WIDTH, (SCREEN_HEIGHT - 200) / 2);
	p_boss->SetBossHP(100);
	AmoObject* p_boss_amo_list = new AmoObject[5];
	for (int i = 0; i < 5; ++i)
	{
		AmoObject* p_boss_amo = p_boss_amo_list + i;
		p_boss->InitAmo(p_boss_amo);
	}

	//Explosion setup
	explosion_main.LoadImg("exp_main.png");
}

void MakePlayerAmo()
{
	for (int i = 0; i < plane.GetAmoList().size(); ++i)
	{
		std::vector<AmoObject*> amo_list = plane.GetAmoList();
		AmoObject* p_amo = amo_list.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Display(g_screen);
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if (p_amo != NULL)
				{
					amo_list.erase(amo_list.begin() + i);
					plane.SetAmoList(amo_list);

					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void DisplayExplosion(SDL_Rect obj1, SDL_Rect obj2)
{
	for (int exp = 0; exp < 4; ++exp)
	{
		int x_pos = (obj1.x + obj1.w*0.5) - EXP_WIDTH*0.5;
		int y_pos = (obj1.y +obj1.h*0.5) - EXT_HEIGHT*0.5;

		explosion_main.set_frame(exp);
		explosion_main.SetRect(x_pos, y_pos);
		explosion_main.DisplayExplosion(g_screen);

		SDL_Delay(50);
		if (SDL_Flip(g_screen) == -1)
			return;
	}
}

void MakeThreat()
{
	for (int i = 0; i < NUM_THREAT; ++i)
	{
		ThreatObject* p_threat = p_threats + i;
		p_threat->Display(g_screen);
		p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
		p_threat->set_x_val(speed);
		p_threat->ThreatShoot(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

		//Check Collision main and threat
		if (CheckCollision(plane.GetRect(), p_threat->GetRect()))
		{
			DisplayExplosion(plane.GetRect(), p_threat->GetRect());
			MessageBox(NULL, "Game Over", "Info", NULL);
			GAME_OVER = true;
		}

		//Check collision threat's amo and plane
		vector<AmoObject*> threats_amo_list = p_threat->GetAmoList();
		for (int i = 0; i < threats_amo_list.size(); ++i)
		{
			AmoObject* threat_amo = threats_amo_list.at(i);
			if (threat_amo)
			{
				if (CheckCollision(threat_amo->GetRect(), plane.GetRect()))
				{
					DisplayExplosion(plane.GetRect(), threat_amo->GetRect());
					MessageBox(NULL, "Game Over", "Info", NULL);
					GAME_OVER = true;
				}
			}
		}

		//Check collision plane's amo and threat
		vector<AmoObject*> plane_amo_list = plane.GetAmoList();
		for (int i = 0; i < plane_amo_list.size(); ++i)
		{
			AmoObject* plane_amo = plane_amo_list.at(i);
			if (plane_amo)
			{
				if (CheckCollision(p_threat->GetRect(), plane_amo->GetRect()))
				{
					p_threat->Reset(SCREEN_WIDTH + i * 400);
					plane.RemoveAmo(i);
					score += 10;
				}
			}
		}
	}
}

void ClearScreen()
{
	for (int i = 0; i < NUM_THREAT; ++i)
	{
		ThreatObject* p_threat = p_threats + i;
		p_threat->Reset(SCREEN_WIDTH + i * 400);
		vector<AmoObject*> threats_amo_list = p_threat->GetAmoList();
		for (int i = 0; i < threats_amo_list.size(); ++i)
		{
			AmoObject* p_amo = threats_amo_list.at(i);
			if (p_amo)
			{
				p_threat->ResetAmo(p_amo);
			}
		}
	}
}

void MakeBoss()
{
	int randNum = ((double)rand() / RAND_MAX) * 60 + 30;
	int x_desPos = SCREEN_WIDTH / 2 + randNum * ((SCREEN_WIDTH / 2) / 100);
	int y_desPos = randNum * ((SCREEN_HEIGHT - 200) / 2) / 100;
	srand(time(NULL));
	//Boss show up
	p_boss->Display(g_screen);
	p_boss->BossMoveOut();

	// Handle Bose Movement
	if (p_boss->GetRect().x != x_desPos && p_boss->GetRect().y != y_desPos)
	{
		p_boss->HandleBossMove(x_desPos, y_desPos);
	}
	else
	{
		randNum = ((double)rand() / RAND_MAX) * 60 + 30;
		x_desPos = SCREEN_WIDTH / 2 + (randNum * (SCREEN_WIDTH / 2) / 100);
		y_desPos = (randNum * ((SCREEN_HEIGHT - 200) / 2) / 100) * 2;
	}

	//Boss shoot
	p_boss->BossShoot(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Check Collision main and boss
	if (CheckCollision(plane.GetRect(), p_boss->GetRect()))
	{
		DisplayExplosion(plane.GetRect(), p_boss->GetRect());
		MessageBox(NULL, "Game Over", "Info", NULL);
		GAME_OVER = true;
	}

	//Check collision boss's amo and plane
	vector<AmoObject*> boss_amo_list = p_boss->GetAmoList();
	for (int i = 0; i < boss_amo_list.size(); ++i)
	{
		AmoObject* boss_amo = boss_amo_list.at(i);
		if (boss_amo)
		{
			if (CheckCollision(boss_amo->GetRect(), plane.GetRect()))
			{
				DisplayExplosion(plane.GetRect(), boss_amo->GetRect());
				MessageBox(NULL, "Game Over", "Info", NULL);
				GAME_OVER = true;
				break;
			}
		}
	}

	//Check damage plane make to boss
	vector<AmoObject*> plane_amo_list = plane.GetAmoList();
	for (int i = 0; i < plane_amo_list.size(); ++i)
	{
		AmoObject* plane_amo = plane_amo_list.at(i);
		if (plane_amo)
		{
			if (CheckCollision(p_boss->GetRect(), plane_amo->GetRect()))
			{
				p_boss->SetBossHP((p_boss->GetBossHP() - 5));
				plane.RemoveAmo(i);
				score += 30;
			}
		}
	}
	if (p_boss->GetBossHP() <= 0)
	{
		DisplayExplosion(p_boss->GetRect(), plane.GetRect());
		MessageBox(NULL, "Game Over! \n Congratulation! You have won!", "Info", NULL);
		GAME_OVER = true;
	}
}

void DisplayScore(const char* score)
{
	TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
	SDL_Color foregroundColor = { 255, 255, 255 };
	SDL_Color backgroundColor = { 49, 49, 49 };
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, score, foregroundColor, backgroundColor);
	SDL_Rect textLocation = { SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100, 0, 0 };
	ApplySurface(textSurface, g_screen, textLocation.x, textLocation.y);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}


int main(int argc, char *argv[])
{
	int backgorund_x = 0;
	bool is_quit = false;
	char char_score[35];

	if (Init() == false)
		return 1;

	if (ShowMenu() == false)
	{
		CleanUp();
		Mix_FreeMusic(music_background);
		return 1;
	}

	SDL_FreeSurface(g_menu);
	g_bkground = LoadImage("background.jpg");
	ApplySurface(g_bkground, g_screen, 0, 0);
	InitCharacterToGame();

	music_background = Mix_LoadMUS("music_background.wav");
	if (Mix_PlayMusic(music_background, -1) == -1)
		return 1;

	//GAME LOOP
	while (!is_quit && !GAME_OVER)
	{
		ApplySurface(g_bkground, g_screen, backgorund_x, 0);
		//Handle player's movement
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			plane.HandleInputAction(g_event);
		}
		plane.Display(g_screen);
		plane.HandleMove();
		//Player make amo
		MakePlayerAmo();
		//Threats set up
		MakeThreat();
		if (backgorund_x >= -1200)
		{
			backgorund_x -= 2;
		}
		else
		{
			//Clear screen for boss
			ClearScreen();
			MakeBoss();
		}

		DisplayScore(_itoa(score, char_score, 10));
		if (SDL_Flip(g_screen) == -1)
			return 1;
	}

	CleanUp();
	Mix_FreeMusic(music_background);
	return 0;
}