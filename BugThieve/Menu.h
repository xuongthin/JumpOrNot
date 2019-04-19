#pragma once

#include "Global.h"
#include "Object.h"
#include "SupportMain.h"

class Tile : public Object
{
public:
	Tile() { ; }
	~Tile() { ; }
};

enum {
	three_buttons = 0, game_name, selection, instruction, delay_start, lose, win, stop_menu, LWmenu
};

class Menu
{
public:
	Menu() { selection_ = 0; }
	~Menu() { ; }

	bool LoadTextureMenu(SDL_Renderer* screen, SupportMain &address);
	void ShowMenu(SDL_Renderer* screen, SupportMain& address, SDL_Event event, bool &close_game, bool &playing);
	void ShowSM(SDL_Renderer* screen);
	void ShowInstruction(SDL_Renderer* screen);
	void ShowDelay(SDL_Renderer* screen);
	void ShowStopMenu(SDL_Renderer* screen, SupportMain &address, SDL_Event event, bool &close_game, bool &end_level, bool& loop);
	void ShowEndMenu(SDL_Renderer* screen, bool win);
private:
	int selection_;
	Tile Texture_[9];
};