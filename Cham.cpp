#include "Cham.h"

Cham::Cham() {
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			pos_[i][j] = true;
		}
	}
	status_ = false;
}

bool Cham::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = BackGround::LoadImg(path, screen);;
	name_cham_ = path;
	return ret;
}

void Cham::ShowCham(SDL_Renderer* des) {
	LoadImg(name_cham_, des);
	int k = 0;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			ChangeRect(j * SIZE_PIXEL, i * SIZE_PIXEL);
			if (pos_[i][j] == true) {
				SDL_Rect renderQuad = { rect_.x - map_x_ , rect_.y - map_y_, rect_.w, rect_.h };
				SDL_RenderCopy(des, p_project_, NULL, &renderQuad);
				if (k == 0) {
					status_ = false;
					k++;
				}
				
			}

		}
	}

}

void Cham::Delete(int x, int y) {
	if (x % SIZE_PIXEL == 0 && y % SIZE_PIXEL == 0) {
		pos_[y/SIZE_PIXEL][x/SIZE_PIXEL] = false;
	}
	status_ = true;
	
}

bool Cham::WinCham() {
	if (status_ == true) return true;
	else return false;
}