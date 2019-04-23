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

	fclose(fp);
	
	bool ret = LoadImg(map_image, des);
	return ret;
}

std::vector<std::vector<int>> BaseMap::MapData()
{
	return solid_;
}