
#include "Menu.h"

bool Menu::LoadTextureMenu(SDL_Renderer* screen, SupportMain &address)
{
	if (!Texture_[three_buttons].LoadImg(address.ImageThreeButton(), screen))
		return false;

	if (!Texture_[game_name].LoadImg(address.ImageGameName(), screen))
		return false;

	if (!Texture_[selection].LoadImg(address.ImageSelection(), screen))
		return false;

	if (!Texture_[instruction].LoadImg(address.ImageInstruction(), screen))
		return false;

	if (!Texture_[delay_start].LoadImg(address.ImageDelay(), screen))
		return false;

	if (!Texture_[lose].LoadImg(address.ImageLose(), screen))
		return false;

	if (!Texture_[win].LoadImg(address.ImageWin(), screen))
		return false;

	if (!Texture_[stop_menu].LoadImg(address.ImageStop(), screen))
		return false;

	if (!Texture_[LWmenu].LoadImg(address.ImageLWMenu(), screen))
		return false;

	return true;
}

void Menu::ShowMenu(SDL_Renderer* screen, SupportMain& address, SDL_Event event, bool &close_game, bool &playing)
{
	SDL_Delay(125);
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			selection_++;
			selection_ = selection_ % 3;
			ShowSM(screen);
			SDL_FlushEvent(SDL_KEYDOWN);
			break;
		}
		case SDLK_LEFT:
		{
			if (selection_ == 0)
			{
				selection_ = 2;
			}
			else
			{
				selection_--;
			}
			selection_ = selection_ % 3;
			ShowSM(screen);
			SDL_FlushEvent(SDL_KEYDOWN);
			break;
		}
		case SDLK_RETURN:
		{
			playing = true;
			break;
		}
		case SDLK_SPACE:
		{
			playing = true;
			break;
		}
		default:
			break;
		}
	}


	if (playing)
	{
		switch (selection_ % 3)
		{
		case 0:
		{
			selection_ = 0;
			break;
		}
		case 1:
		{
			address.Restart();
			selection_ = 0;
			break;
		}
		case 2:
		{
			close_game = true;
			selection_ = 0;
			break;
		}
		default:
			break;
		}
	}
}

void Menu::ShowSM(SDL_Renderer* screen)
{
	SDL_RenderClear(screen);
	Texture_[three_buttons].Render(screen, NULL);
	Texture_[game_name].Render(screen, NULL);
	SDL_Rect rect_location = { 316 * selection_ + 166, 0, 316, 800 };
	Texture_[selection].Render(screen, &rect_location);
	SDL_RenderPresent(screen);
}

void Menu::ShowInstruction(SDL_Renderer* screen)
{
	SDL_RenderClear(screen);
	Texture_[instruction].Render(screen, NULL);
	SDL_RenderPresent(screen);
}

void Menu::ShowDelay(SDL_Renderer* screen)
{
	Texture_[delay_start].Render(screen, NULL);
}

void Menu::ShowStopMenu(SDL_Renderer* screen, SupportMain &address, SDL_Event event, bool &close_game, bool &end_level, bool &loop)
{
	bool stop = true;
	selection_ = selection_ % 3;

	SDL_RenderClear(screen);
	Texture_[three_buttons].Render(screen, NULL);
	Texture_[stop_menu].Render(screen, NULL);
	SDL_Rect rect_location = { 166 + 316 * (selection_ % 3), 0, 316, 800 };
	Texture_[selection].Render(screen, &rect_location);
	SDL_RenderPresent(screen);
	SDL_Delay(150);
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			selection_++;
			SDL_FlushEvent(SDL_KEYDOWN);
			break;
		}
		case SDLK_LEFT:
		{
			if (selection_ == 0)
			{
				selection_ = 2;
			}
			else
			{
				selection_--;
			}
			SDL_FlushEvent(SDL_KEYDOWN);
			break;
		}
		case SDLK_RETURN:
		{
			stop = false;
			SDL_FlushEvent(SDL_KEYDOWN);
			break;
		}
		case SDLK_SPACE:
		{
			stop = false;
			loop = false;
			SDL_FlushEvent(SDL_KEYDOWN);
			break;
		}
		default:
			break;
		}
	}

	if (!loop)
	{
		switch (selection_ % 3)
		{
		case 0:
		{
			selection_ = 0;
			break;
		}
		case 1:
		{
			address.Restart();
			end_level = true;
			selection_ = 0;
			break;
		}
		case 2:
		{
			close_game = true;
			selection_ = 0;
			break;
		}
		default:
			break;
		}
	}
}

void Menu::ShowEndMenu(SDL_Renderer* screen, bool won)
{
	SDL_RenderClear(screen);
	if (won)
	{
		Texture_[win].Render(screen, NULL);
	}
	else
	{
		Texture_[lose].Render(screen, NULL);
	}
	SDL_RenderPresent(screen);
}
