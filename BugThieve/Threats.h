
#ifndef THREATS_H_
#define THREATS_H_

#include "Global.h"
#include "Object.h"

#define COLLISION_RADIUS 40

struct TrapSaw
{
	int x_center_;
	int y_center_;
	int x_radius_;
	int y_radius_;
	int x_coordinate_;
	int y_coordinate_;
	float phi_;
	float angular_frequency_;
	TrapSaw(int x_center, int y_center, int x_radius, int y_radius, float angle, float frequency)
	{
		x_center_ = (x_center - 1) * BASIC_SIZE + BASIC_SIZE / 2;
		y_center_ = (y_center - 1) * BASIC_SIZE + BASIC_SIZE / 2;
		x_radius_ = x_radius * BASIC_SIZE;
		y_radius_ = y_radius * BASIC_SIZE;
		phi_ = angle;
		angular_frequency_ = frequency;
		
	}

	void UpdateTrap()
	{
		x_coordinate_ = (int) (x_center_ + x_radius_ * cos(phi_));
		y_coordinate_ = (int) (y_center_ + y_radius_ * sin(phi_));
		phi_ += angular_frequency_ / FPS;
	}

};

class TrapList : public Object
{
public:
	TrapList() { ; }
	~TrapList();
	void LoadThreats(const std::string &trap_image, const std::string &traps_list, SDL_Renderer* des);
	bool Impact(SDL_Point bug_center);
	void ShowTraps(SDL_Renderer * screen);
private:
	std::vector <TrapSaw> traps_list_;
};

#endif // !THREAT_H_
