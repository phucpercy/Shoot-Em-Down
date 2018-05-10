#include "Common_Function.h"
#include <cmath>

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
	SDL_Surface* loadImage = NULL;
	SDL_Surface* optimizeImage = NULL;

	loadImage = IMG_Load(file_path.c_str());
	if (loadImage != NULL)
	{
		optimizeImage = SDL_DisplayFormat(loadImage);
		SDL_FreeSurface(loadImage);
		if (optimizeImage != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimizeImage->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimizeImage, SDL_SRCCOLORKEY, color_key);
		}
	}

	return optimizeImage;
}

void SDLCommonFunc::ApplySurface(SDL_Surface* scr, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, NULL, des, &offset);
}

void SDLCommonFunc::ApplyClip(SDL_Surface* scr, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(scr, clip, des, &offset);
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object_1, const SDL_Rect& object_2)
{
	int ob1_radius = object_1.h / 2;
	int ob2_radius = object_2.h / 2;
	int ob1_x_val = object_1.x + object_1.w / 2;
	int ob1_y_val = object_1.y + object_1.h / 2;
	int ob2_x_val = object_2.x + object_2.w / 2;
	int ob2_y_val = object_2.y + object_2.h / 2;

	int ob_distance = sqrt((ob1_x_val - ob2_x_val)*(ob1_x_val - ob2_x_val) + (ob1_y_val - ob2_y_val)*(ob1_y_val - ob2_y_val));
 
	if (ob_distance < (ob1_radius + ob2_radius))
		return true;

	return false;
}

void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}