#ifndef Game_map_h
#define Game_map_h

#include "background.h"
#include "function.h"

class Pixel :public BackGround {
public:
	Pixel() { ; };
	~Pixel() { ; };
};

class GameMap {
public:
	GameMap();
	~GameMap();

	void LoadMap(const char* name);
	void LoadPixel(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);

	Map GetMap() { return game_map_; };
	void Setmap(Map& game_map) { game_map_ = game_map; }

private:
	Map game_map_;
	Pixel pixel_[MAX_TYPE_PIXEL];

};






#endif // !tile_map_h
