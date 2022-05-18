#include "tile_map.h"

GameMap::GameMap() {
	game_map_.now_x_ = 0;
	game_map_.now_y_ = 0;
	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
}

GameMap:: ~GameMap() {

}

void GameMap::LoadMap(const char* name) {
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) return;

	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			fscanf_s(fp, "%d", &game_map_.pixel_map_[i][j]);
			int val = game_map_.pixel_map_[i][j];
			if (val >= 0) {
				if (j > game_map_.max_x_) game_map_.max_x_ = j;
				if (i > game_map_.max_y_) game_map_.max_y_ = i;
			}
		}
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1) * SIZE_PIXEL;
	game_map_.max_y_ = (game_map_.max_y_ + 1) * SIZE_PIXEL;

	game_map_.file_name_ = name;
	fclose(fp);
}

void GameMap::LoadPixel(SDL_Renderer* screen) {
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TYPE_PIXEL; i++) {
		sprintf_s(file_img, "map/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) continue;

		fclose(fp);
		pixel_[i].LoadImg(file_img, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.now_x_ / SIZE_PIXEL;

	x1 = (game_map_.now_x_ % SIZE_PIXEL) * (-1);
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : SIZE_PIXEL);

	map_y = game_map_.now_y_ / SIZE_PIXEL;

	y1 = (game_map_.now_y_ % SIZE_PIXEL) * (-1);
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : SIZE_PIXEL);

	for (int i = y1; i < y2; i += SIZE_PIXEL) {
		map_x = game_map_.now_x_ / SIZE_PIXEL;
		for (int j = x1; j < x2; j += SIZE_PIXEL) {
			int val = game_map_.pixel_map_[map_y][map_x];
			if (val >= 0) {
				pixel_[val].ChangeRect(j, i);
				pixel_[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}
