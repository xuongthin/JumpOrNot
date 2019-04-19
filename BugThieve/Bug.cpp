
#include "Bug.h"

Bug::Bug()
{
	status_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	order_ = 0;
	on_wall_ = false;
	on_walk_ = false;
	face_ = 1;
	y_velocity_ = 0;
}

Bug::~Bug()
{
	;
}

void Bug::LoadTheBug(std::string path, SDL_Renderer* screen, int life)
{
	sound = Mix_LoadWAV("datas/sound/jumping.wav");

	bool ret = LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / 6;
		height_frame_ = rect_.h;
	}

	life_ = life;
}

void Bug::LoadStart(SDL_Point start_point)
{
	x_pos_ = start_point.x * BASIC_SIZE + 4;
	y_pos_ = start_point.y * BASIC_SIZE + 4;
}

void Bug::InputOrder(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		{
			order_ = 10;
		}
		case SDLK_SPACE:
		{
			order_ = 10;
		}
		default:
			break;
		}
	}
}

void Bug::Update()
{
	if (order_ > 0)
	{
		order_--;
	}

	switch (status_)
	{
	case 0:
	{
		y_pos_ += (int)y_velocity_;
		y_velocity_ += GRAVITY;
		x_pos_ += face_ * SPEECH;
		break;
	}
	case 1:
	{
		if (order_ > 0)
		{
			Mix_PlayChannel(1, sound, 0);
			order_ = 0;
			y_velocity_ = JUMP_VELOCITY;
			y_pos_ += (int)y_velocity_;
			y_velocity_ += GRAVITY;
		}
		break;
	}
	case 2:
	{
		if (order_ > 0)
		{
			Mix_PlayChannel(1, sound, 0);
			order_ = 0;
			y_velocity_ = JUMP_VELOCITY;
			y_pos_ += (int) y_velocity_;
			y_velocity_ += GRAVITY;
			face_ = -face_;
			x_pos_ += face_ * SPEECH;
		}
		else
		{
			y_pos_ += (int)y_velocity_;
			y_velocity_ += GRAVITY;
			if (y_velocity_ > MAX_SLIDING_SPEECH)
			{
				y_velocity_ = MAX_SLIDING_SPEECH;
			}
		}
		break;
	}
	case 3:
	{
		x_pos_ += face_ * SPEECH;

		if (order_ > 0)
		{
			Mix_PlayChannel(1, sound, 0);
			order_ = 0;
			y_velocity_ = JUMP_VELOCITY;
			y_pos_ += (int) y_velocity_;
			y_velocity_ += GRAVITY;
		}
		else
		{
			y_velocity_ = 0;
		}
		break;
	}
	default:
		break;
	}
}

void Bug::Show(SDL_Renderer * screen)
{
	SDL_Rect rect = { x_pos_ + MARGIN_LEFT, y_pos_ + MARGIN_TOP, width_frame_, height_frame_ };

	switch (status_)
	{
	case 0:
	{
		if (face_ == 1)
		{
			SDL_RenderCopy(screen, p_object_, &left_basic_frame_, &rect);
		}
		else
		{
			SDL_RenderCopy(screen, p_object_, &right_basic_frame_, &rect);
		}
		break;
	}
	case 1:
	{

		if (face_ > 0)
		{
			SDL_RenderCopy(screen, p_object_, &right_corner_frame_, &rect);
		}
		else
		{
			SDL_RenderCopy(screen, p_object_, &left_corner_frame_, &rect);
		}
		break;
	}
	case 2:
	{

		if (face_ > 0)
		{
			SDL_RenderCopy(screen, p_object_, &right_frame_, &rect);
		}
		else
		{
			SDL_RenderCopy(screen, p_object_, &left_frame_, &rect);
		}
		break;
	}
	case 3:
	{
		if (jelly_ > 0)
		{
			rect.y = y_pos_ + MARGIN_TOP + (int) jelly_;
			rect.h = height_frame_ - (int) jelly_;
			jelly_ -= 1;
		}
		if (face_ == 1)
		{
			SDL_RenderCopy(screen, p_object_, &left_basic_frame_, &rect);
		}
		else
		{
			SDL_RenderCopy(screen, p_object_, &right_basic_frame_, &rect);
		}
		break;
	}
	default:
		break;
	}
}

void Bug::UpdateStatus(std::vector<std::vector<int>> map_data)
{
	SDL_Point p_top_left = { (x_pos_ + BASIC_SIZE) / BASIC_SIZE
				  		   , (y_pos_ - 1 + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_top_right = { (x_pos_ + width_frame_ - 1 + BASIC_SIZE) / BASIC_SIZE
						    , (y_pos_ - 1 + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_left_top = { (x_pos_ - 1 + BASIC_SIZE) / BASIC_SIZE
						   , (y_pos_ + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_right_top = { (x_pos_ + width_frame_ + 1 + BASIC_SIZE) / BASIC_SIZE
							, (y_pos_ + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_left_bottom = { (x_pos_ - 1 + BASIC_SIZE) / BASIC_SIZE
					   	      , (y_pos_ + height_frame_ * 4 / 5 + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_right_bottom = { (x_pos_ + width_frame_ + 1 + BASIC_SIZE) / BASIC_SIZE
							   , (y_pos_ + height_frame_ * 4 / 5 + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_bottom_left = { (x_pos_ + BASIC_SIZE) / BASIC_SIZE
							  , (y_pos_ + height_frame_ + 1 + BASIC_SIZE) / BASIC_SIZE };

	SDL_Point p_bottom_right = { (x_pos_ + width_frame_ - 1 + BASIC_SIZE) / BASIC_SIZE
							   , (y_pos_ + height_frame_ + 1 + BASIC_SIZE) / BASIC_SIZE };

	status_ = air;

	if (map_data[p_right_top.y][p_right_top.x] == 1 || map_data[p_left_top.y][p_left_top.x] == 1)
	{
		status_ = wall;
	}

	if (map_data[p_left_bottom.y][p_left_bottom.x] == 1 || map_data[p_right_bottom.y][p_right_bottom.x] == 1)
	{
		status_ = wall;
		on_wall_ = false;
	}

	if (map_data[p_bottom_left.y][p_bottom_left.x] == 1 || map_data[p_bottom_right.y][p_bottom_right.x] == 1)
	{
		if ((y_pos_ + height_frame_ + 1) % BASIC_SIZE > 0)
		{
			jelly_ = 16;
		}
		y_pos_ -= (y_pos_ + height_frame_ + 1) % BASIC_SIZE;
		on_walk_ = true;
		y_velocity_ = 0;
		if (status_ == wall)
		{
			status_ = corner;
		}
		else
		{
			status_ = ground;
		}
	}

	if (map_data[p_top_left.y][p_top_left.x] == 1 || map_data[p_top_right.y][p_top_right.x] == 1)
	{
		y_velocity_ = 0;
		if (BASIC_SIZE + 1 - (y_pos_ + BASIC_SIZE) % BASIC_SIZE < BASIC_SIZE / 2)
		{
			y_pos_ += BASIC_SIZE + 1 - (y_pos_ + BASIC_SIZE) % BASIC_SIZE;
		}
		else
		{
			y_pos_ += 5;
		}
		//status_ = ceiling;
	}
}

SDL_Point Bug::GetCenter()
{
	SDL_Point center = { x_pos_ + width_frame_ / 2 , y_pos_ + height_frame_ / 2 };

	return center;
}

void Bug::Appear(SDL_Renderer* screen)
{
	int i = 10;
	double angle = 0;

	while (i--)
	{
		int start = SDL_GetTicks();
		angle += 10;
		SDL_Rect rect_location = { x_pos_, y_pos_, rect_.w, rect_.h };
		SDL_RenderCopyEx(screen, p_object_, NULL, &rect_location, angle, NULL, SDL_FLIP_NONE);
		int end = SDL_GetTicks();
		int delay = 1000 / FPS - (end - start);
		SDL_Delay(delay > 0 ? delay : 0);
	}
}
