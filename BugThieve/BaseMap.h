
#ifndef MAP_H_
#define MAP_H_

#include "Global.h"
#include "Object.h"

// #define COLLISION_RADIUS 40

class BaseMap : public Object
{
public:
	BaseMap();
	~BaseMap() { ; }

	bool LoadMap(const std::string &map_name, const std::string & map_image, SDL_Renderer* des);
	std::vector <std::vector<int>>  MapData();
	// void LoadThreats(const std::string &trap_image, const std::string &traps_list);
	// bool Impact(int x_bug, int y_bug);
private:
	std::vector <std::vector<int>> solid_;
};

#endif // MAP_H_