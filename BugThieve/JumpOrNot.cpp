
#include "Global.h"
#include "Object.h"
#include "Bug.h"
#include "BaseMap.h"
#include "Threats.h"
#include "Exit.h"
#include "SupportMain.h"
#include "Menu.h"

#undef main

bool InitData()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("JumpOrNot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void Close()
{
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main()
{
	if (InitData() == false)
	{
		printf("ERROR: InitData()");
		return -1;
	}

	SupportMain address;
	address.LoadLifeImg(g_screen);
	address.UpdateLevel(false);

	Menu menu;
	if (!menu.LoadTextureMenu(g_screen, address))
	{
		printf("ERROR: Load menu");
		return -1;
	}

	Object g_background;
	if (!g_background.LoadImg(address.ImageBkG(), g_screen))
	{
		printf("ERROR: LoadImg-background");
		return -1;
	}

	bool close_game = false;
	while (!close_game)
	{
		bool playing = false;
		menu.ShowSM(g_screen);
		while (!playing)
		{
			if (g_event.type == SDL_QUIT)
			{
				close_game = true;
				break;
			}
			while (SDL_PollEvent(&g_event) != 0)
			{
				menu.ShowMenu(g_screen, address, g_event, close_game, playing);
			}
		}

		if (close_game)
		{
			break;
		}

		menu.ShowInstruction(g_screen);
		while (true)
		{
			if (SDL_PollEvent(&g_event) != 0)
			{
				if (g_event.type == SDL_QUIT)
				{
					close_game = true;
					break;
				}
				if (g_event.key.keysym.sym == SDLK_ESCAPE)
				{
					break;
				}
			}
		}

		if (close_game)
		{
			break;
		}

		while(playing)
		{
			bool end_level = false;
			bool go_off = false;
			bool restart = false;

			BaseMap the_base;
			if (!the_base.LoadMap(address.DataBase(), address.ImageBase(), g_screen))
			{
				printf("ERROR: LoadMap");
				return -1;
			}

			Door doors;
			if (!doors.LoadDoor(address.DataDoor(), address.ImageDoor(), g_screen))
			{
				printf("ERROR: LoadDoor");
				return -1;
			}

			Bug the_bug;
			the_bug.LoadTheBug(address.ImageBug(), g_screen, 5);
			the_bug.LoadStart(doors.GetStart());

			TrapList trap_list;
			trap_list.LoadThreats(address.ImageTrap(), address.DataTrap(), g_screen);

			SDL_RenderClear(g_screen);
			g_background.Render(g_screen, NULL);
			the_base.Render(g_screen, NULL);
			the_bug.Show(g_screen);
			trap_list.ShowTraps(g_screen);
			doors.ShowExit(g_screen);
			address.ShowLife(g_screen);
			the_bug.UpdateStatus(the_base.MapData());
			menu.ShowDelay(g_screen);
			SDL_RenderPresent(g_screen);

			while (true)
			{
				if (SDL_PollEvent(&g_event) != 0)
				{
					if (g_event.type == SDL_QUIT)
					{
						close_game = true;
						break;
					}
					if (g_event.key.keysym.sym == SDLK_UP || g_event.key.keysym.sym == SDLK_SPACE || g_event.key.keysym.sym == SDLK_RETURN)
					{
						break;
					}
				}
			}

			if (close_game)
			{
				break;
			}

			while (!(end_level || go_off || restart))
			{
				int start = SDL_GetTicks();

				bool pause = false;
				while (SDL_PollEvent(&g_event) != 0 || pause)
				{
					if (g_event.type == SDL_QUIT)
					{
						close_game = true;
						break;
					}

					if (g_event.key.keysym.sym == SDLK_ESCAPE)
					{
						pause = true;
					}

					if (pause)
					{
						menu.ShowStopMenu(g_screen, address, g_event, close_game, restart, pause);
					}
					else
					{
						the_bug.InputOrder(g_event);
					}
				}

				if (close_game || restart)
				{
					break;
				}

				SDL_RenderClear(g_screen);

				g_background.Render(g_screen, NULL);
				the_base.Render(g_screen, NULL);
				the_bug.Show(g_screen);
				trap_list.ShowTraps(g_screen);
				doors.ShowExit(g_screen);
				address.ShowLife(g_screen);

				go_off = trap_list.Impact(the_bug.GetCenter());
				end_level = doors.Exit(the_bug.GetCenter());

				the_bug.Update();
				the_bug.UpdateStatus(the_base.MapData());
				SDL_RenderPresent(g_screen);

				int end = SDL_GetTicks();
				int delay = 1000 / FPS - (end - start);
				SDL_Delay(delay > 0 ? delay : 0);
			}

			if (close_game)
			{
				break;
			}

			if (restart)
			{
				address.Restart();
			}
			else
			{
				address.UpdateLevel(end_level);
			}
			address.Save();

			if (address.GetLife() == 0 || address.GetLevel() == 10)
			{
				playing = false;
			}

			trap_list.Free();
			the_bug.Free();
			the_base.Free();
		}

		if (close_game)
		{
			break;
		}

		menu.ShowEndMenu(g_screen, address.GetLife());
		address.Restart();
		SDL_Delay(2000);
		SDL_FlushEvent(SDL_KEYDOWN);
		while (true)
		{
			if (SDL_PollEvent(&g_event) != 0)
			{
				if (g_event.type == SDL_QUIT || g_event.key.keysym.sym == SDLK_ESCAPE)
				{
					close_game = true;
					break;
				}
				if (g_event.key.keysym.sym == SDLK_RETURN)
				{
					break;
				}
			}
		}
	}
	address.Save();

	Close();
	g_background.Free();
	return 1;
}
