#pragma once

#include "Global.h"
#include "Object.h"

#define IMPACT_RADIUS 40

class Door : public Object
{
public:
	Door();
	~Door();
	bool LoadDoor(std::string door_data, std::string door_image, SDL_Renderer* screen);
	SDL_Point GetStart();
	void ShowExit(SDL_Renderer * screen);
	bool Exit(SDL_Point center);
private:
	int gateaway_x_;
	int gateaway_y_;

	int exit_x_;
	int exit_y_;
};