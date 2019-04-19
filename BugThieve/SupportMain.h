#pragma once
#include "Global.h"
#include "Object.h"
#include <fstream>

const int MAX_BASE = 9;
const int ORIGINAL_LIFE = 10;

class SupportMain : public Object
{
public:
	SupportMain();
	~SupportMain();

	void UpdateLevel(bool over);
	void Save();
	void LoadLifeImg(SDL_Renderer* screen);
	void ShowLife(SDL_Renderer* screen);
	int GetLife() { return life_; }
	int GetLevel() { return level_; }
	std::string ImageBkG() { return image_background_; }
	std::string ImageBug() { return image_bug_; }
	std::string ImageBase() { return image_base_; }
	std::string ImageTrap() { return image_trap_; }
	std::string ImageDoor() { return image_door_; }

	std::string DataBase() { return data_base_; }
	std::string DataTrap() { return data_trap_; }
	std::string DataDoor() { return data_door_; }

	std::string ImageThreeButton() { return image_three_button_; }
	std::string ImageInstruction() { return image_instruction_; } 
	std::string ImageGameName() { return image_game_name_; }
	std::string ImageSelection() { return image_selection_; }
	std::string ImageDelay() { return image_delay_; }
	std::string ImageLose() { return image_lose_; }
	std::string ImageWin() { return image_win_; }
	std::string ImageStop() { return image_stop_; }
	std::string ImageLWMenu() { return image_LW_menu_; }

	void Restart();
private:
	int level_;
	int life_;

	std::string image_heart_;
	std::string image_background_;
	std::string image_bug_;
	std::string image_base_;
	std::string image_trap_;
	std::string image_door_;

	std::string data_base_;
	std::string data_trap_;
	std::string data_door_;

	std::string image_three_button_; // 3 buttons
	std::string image_instruction_;
	std::string image_game_name_;
	std::string image_selection_;
	std::string image_delay_;
	std::string image_lose_;
	std::string image_win_;
	std::string image_stop_;
	std::string image_LW_menu_;
};

