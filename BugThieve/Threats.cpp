#include "Threats.h"

TrapList::~TrapList()
{
	traps_list_.erase(traps_list_.begin(), traps_list_.end());
	Object::Free();
}

void TrapList::LoadThreats(const std::string & trap_image, const std::string & traps_data, SDL_Renderer * des)
{
	FILE* fp = NULL;
	int amount_traps;
	int x_center;
	int y_center;
	int x_radius;
	int y_radius;
	float angle;
	float frequency;

	fopen_s(&fp, traps_data.c_str(), "rb");
	if (fp == NULL)
	{
		return;
	}

	fscanf_s(fp, "%d", &amount_traps);

	for (int i = 0; i < amount_traps; i++)
	{
		fscanf_s(fp, "%d %d %d %d %f %f", &x_center, &y_center, &x_radius, &y_radius, &angle, &frequency);
		TrapSaw saw(x_center, y_center, x_radius, y_radius, angle, frequency);
		traps_list_.push_back(saw);
	}
	fclose(fp);
	
	LoadImg(trap_image, des);
}

bool TrapList::Impact(SDL_Point bug_center)
{
	for (int i = 0; i != traps_list_.size(); i++)
	{
		double d;
		d = sqrt(pow(traps_list_[i].x_coordinate_ - bug_center.x, 2) + pow(traps_list_[i].y_coordinate_ - bug_center.y, 2));
		if (d < COLLISION_RADIUS)
		{
			return true;
		}
	}
	return false;
}

void TrapList::ShowTraps(SDL_Renderer * screen)
{
	for (int i = 0; i != traps_list_.size(); i++)
	{
		traps_list_[i].UpdateTrap();

		SDL_Rect rect = { traps_list_[i].x_coordinate_ - rect_.w / 2 + MARGIN_LEFT
						, traps_list_[i].y_coordinate_ - rect_.h / 2 + MARGIN_TOP
						, rect_.w, rect_.h };

		SDL_RenderCopyEx(screen, p_object_, NULL, &rect, traps_list_[i].phi_, NULL, SDL_FLIP_NONE);
	}
}
