#pragma once

#include "function.h"
#include "background.h"

#define SIZEFIRE 8

class Fire : public BackGround {
public:
	Fire(int x, int y);
	bool DeleteBackGround(string path, SDL_Renderer* screen);
	bool LoadImg(string path, SDL_Renderer* g_screen);
	void ShowFire(SDL_Renderer* des);
	void Set_Clip();

	void SetMapXYFire(const int map_x, const int map_y) {
		map_x_ = map_x;
		map_y_ = map_y;
	}

private:
	int x_pos_;
	int y_pos_;

	int map_x_;
	int map_y_;

	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[SIZEFIRE];
	int frame_;

	string name_frame_;
};
