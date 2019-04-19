#pragma once
#ifndef THE_BUG_H_
#define THE_BUG_H_

#include "Global.h"
#include "Object.h"

#define JUMP_VELOCITY -15
#define SPEECH 4
#define GRAVITY 0.75
#define MAX_SLIDING_SPEECH 3

const SDL_Rect left_basic_frame_ = { 80, 0, 40, 40 };
const SDL_Rect right_basic_frame_ = { 120, 0, 40, 40 };
const SDL_Rect left_frame_ = { 40, 0, 40, 40 };
const SDL_Rect left_corner_frame_ = { 0, 0, 40, 40 };
const SDL_Rect right_frame_ = { 160, 0, 40, 40 };
const SDL_Rect right_corner_frame_ = { 200, 0, 40, 40 };

enum {
	air, corner, wall, ground
};

//Mix_Chunk* sound = NULL;


class Bug : public Object
{
public:
	Bug();
	~Bug();

	void LoadTheBug(std::string path, SDL_Renderer* screen, int life);
	void LoadStart(SDL_Point start_point);
	void InputOrder(SDL_Event event);
	void Update();
	void Show(SDL_Renderer * des);
	void UpdateStatus(std::vector<std::vector<int>> map_data);
	SDL_Point GetCenter();
	void Appear(SDL_Renderer *screen);
private:
	int x_pos_;
	int y_pos_;
	int width_frame_;
	int height_frame_;
	int life_;
	int order_;
	float y_velocity_;
	bool on_wall_;
	bool on_walk_;
	int face_;
	float jelly_;
	int status_; // edge = 1; ceiling = 2; air = 3; corner = 4; wall = 5; ground = 6.
	Mix_Chunk* sound = NULL;
};

#endif // !THE_BUG_H_
