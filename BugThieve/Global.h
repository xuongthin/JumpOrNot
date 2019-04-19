#pragma once

#ifndef GLOBAL_H_
#define	GLOBAL_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Windows.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <math.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//static Mix_Chunk* JumpSound = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;
const int MARGIN_LEFT = 80;
const int MARGIN_TOP = 80;

const int COLOR_KEY_R = 0;				// define color
const int COLOR_KEY_G = 255;			//
const int COLOER_KEY_B = 255;			//
const int RENDER_DRAW_COLOR = 0xff;		//

const int MAX_MAP_DATA_X = 16;
const int MAX_MAP_DATA_Y = 10;
const int BASIC_SIZE = 80;

const int FPS = 60;
#endif // GLOBAL_H_
