#ifndef _COMMON_FUNCTION_H_
#define _COMMON_FUNCTION_H_

#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
#undef main

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;
const int NUM_THREAT = 4;

// Image
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_menu = NULL;
static SDL_Event g_event;
static double speed = 5;
static bool GAME_OVER = false;

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y);
	void ApplyClip(SDL_Surface* scr, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2);
}

#endif
