#include "Exit.h"

Door::Door()
{
	;
}

Door::~Door()
{
	Free();
	gateaway_x_ = 0;
	gateaway_y_ = 0;

	exit_x_ = 0;
	exit_y_ = 0;
}

bool Door::LoadDoor(std::string door_data, std::string door_image, SDL_Renderer* screen)
{
	FILE* fp = NULL;

	fopen_s(&fp, door_data.c_str(), "rb");
	if (fp == NULL)
	{
		return false;
	}

	fscanf_s(fp, "%d %d %d %d", &gateaway_x_, &gateaway_y_, &exit_x_, &exit_y_);

	fclose(fp);

	return LoadImg(door_image, screen);
}

SDL_Point Door::GetStart()
{
	SDL_Point start_point = { gateaway_x_, gateaway_y_ };

	return start_point;
}

void Door::ShowExit(SDL_Renderer * screen)
{
	SDL_Rect rect = { exit_x_ * BASIC_SIZE + BASIC_SIZE / 2 - rect_.w / 2 + MARGIN_LEFT
					, exit_y_ * BASIC_SIZE + BASIC_SIZE / 2 - rect_.w / 2 + MARGIN_TOP
					, rect_.w, rect_.h };

	SDL_RenderCopy(screen, p_object_, NULL, &rect);
}

bool Door::Exit(SDL_Point center)
{
	double d = sqrt(pow(center.x - exit_x_ * BASIC_SIZE - BASIC_SIZE / 2, 2) + pow(center.y - exit_y_ * BASIC_SIZE - BASIC_SIZE / 2, 2));
	if (d < IMPACT_RADIUS)
	{
		return true;
	}
	return false;
}
