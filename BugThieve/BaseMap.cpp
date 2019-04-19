#include "BaseMap.h"

BaseMap::BaseMap()
{
	;
}

bool BaseMap::LoadMap(const std::string & map_data, const std::string & map_image, SDL_Renderer* des)
{
	int x;
	FILE* fp = NULL;
	fopen_s(&fp, map_data.c_str(), "rb");
	if (fp == NULL)
	{
		return false;
	}

	for (int i = 0; i < MAX_MAP_DATA_Y; i++)
	{
		std::vector<int> arr;
		for (int j = 0; j < MAX_MAP_DATA_X; j++)
		{
			fscanf_s(fp, "%d", &x);
			arr.push_back(x);
		}
		solid_.push_back(arr);
	}

	//for (int i = 0; i < MAX_MAP_DATA_Y; i++)
	//{
	//	for (int j = 0; j < MAX_MAP_DATA_X; j++)
	//	{
	//		fscanf_s(fp, "%d", &x);
	//		solid_[i].push_back(x);
	//	}
	//}

	fclose(fp);
	
	bool ret = LoadImg(map_image, des);
	return ret;
}

std::vector<std::vector<int>> BaseMap::MapData()
{
	return solid_;
}

//void BaseMap::LoadThreats(const std::string &trap_image, const std::string & traps_list)
//{
//	FILE* fp = NULL;
//	int amount_traps;
//	int x_center;
//	int y_center;
//	int Radius;
//	int angle;
//	int frequency;
//
//	fopen_s(&fp, traps_list.c_str(), "rb");
//	if (fp == NULL)
//	{
//		return;
//	}
//
//	fscanf_s(fp, "%d", &amount_traps);
//	for (int i = 0; i < amount_traps; i++)
//	{
//		fscanf_s(fp, "%d %d %d %d %d", &x_center, &y_center, &Radius, &angle, &frequency);
//		TrapSaw saw(x_center, y_center, Radius, angle, frequency);
//	}
//	fclose(fp);
//	
//
//}

//bool BaseMap::Impact(int x_bug, int y_bug)
//{
//	for (int i = 0; i != trap_list_.size(); i++)
//	{
//		double d;
//		d = sqrt(pow(trap_list_[i].x_coordinate_ - x_bug, 2) + pow(trap_list_[i].y_coordinate_ - y_bug, 2));
//		if (d < COLLISION_RADIUS)
//		{
//			return true;
//		}
//	}
//	return false;
//}
