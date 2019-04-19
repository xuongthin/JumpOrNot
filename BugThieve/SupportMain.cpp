#include "SupportMain.h"



SupportMain::SupportMain()
{
	std::fstream myfile;

	myfile.open("datas/startfile.txt", std::fstream::in);
	myfile >> level_ >> life_;
	if (myfile.fail())
	{
		level_ = 1;
		life_ = ORIGINAL_LIFE;
	}

	image_background_ = "images/others/mainbk.png";
	image_bug_ = "images/others/main.png";
	image_trap_ = "images/others/threat.png";
	image_door_ = "images/others/exit.png";
	image_heart_ = "images/others/heart.png";
	image_three_button_ = "images/menu/threebutton.png";
	image_game_name_ = "images/menu/gamename.png";
	image_stop_ = "images/menu/stop.png";
	image_delay_ = "images/menu/delay.png";
	image_win_ = "images/menu/win.png";
	image_lose_ = "images/menu/lose.png";
	image_LW_menu_ = "images/menu/LWmenu.png";
	image_selection_ = "images/menu/selection.png";
	image_instruction_ = "images/menu/instruction.png";

	myfile.close();
	life_ += 1;
}

SupportMain::~SupportMain()
{
}

void SupportMain::UpdateLevel(bool level_pass)
{
	if (level_pass)
	{
		life_ += 1;
		level_ += 1;
	}
	else
	{
		life_ -= 1;
	}
	char file_name[30];
	sprintf_s(file_name, "images/bases/base0%d.png", (level_ - 1) % MAX_BASE + 1);
	image_base_ = file_name;
	sprintf_s(file_name, "datas/bases/base%d.dat", (level_ - 1) % MAX_BASE + 1);
	data_base_ = file_name;
	sprintf_s(file_name, "datas/traps/trap%d.dat", level_);
	data_trap_ = file_name;
	sprintf_s(file_name, "datas/doors/door%d.dat", level_);
	data_door_ = file_name;

	Save();
}

void SupportMain::Save()
{
	std::fstream myfile;
	myfile.open("datas/startfile.txt", std::fstream::out);
	myfile.clear();
	myfile << level_ << " " << life_;
	myfile.close();
}

void SupportMain::LoadLifeImg(SDL_Renderer* screen)
{
	LoadImg(image_heart_, screen);
}

void SupportMain::ShowLife(SDL_Renderer* screen)
{
	for (int i = 0; i < life_; i++)
	{
		SDL_Rect rect_location = { i * 80, rect_.y, rect_.w, rect_.h };

		SDL_RenderCopy(screen, p_object_, NULL, &rect_location);
	}
}

void SupportMain::Restart()
{
	level_ = 1;
	life_ = ORIGINAL_LIFE;
	UpdateLevel(false);
}
