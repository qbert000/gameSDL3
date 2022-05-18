#pragma once

#include "function.h"
#include "background.h"
#include "character.h"

class Cham : public BackGround {
public:
	Cham();
	void DrawCham(SDL_Renderer* screen);


	bool LoadImg(string path, SDL_Renderer* screen);
	void ShowCham(SDL_Renderer* des);
	void SetMapCham(const int map_x, const int map_y) {
		map_x_ = map_x;
		map_y_ = map_y;
	}

	void Delete(int x, int y);
	bool WinCham();
	
private:
	string name_cham_;

	int map_x_;
	int map_y_;
	
	bool pos_[MAX_MAP_Y][MAX_MAP_X];
	bool status_;
};