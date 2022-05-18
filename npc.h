#pragma once

#include "background.h"
#include "character.h"
#include "function.h"
#include "tile_map.h"
#include "SmartMap.h"

#define SIZENPC 8

class NPC : public BackGround {
public:
	NPC(int x_pos, int y_pos);
	

	
	void SetMapXYNPC(const int map_x, const int map_y) {
		map_x_ = map_x;
		map_y_ = map_y;
	}
	bool LoadImg(string path, SDL_Renderer* g_screen);
	void ShowNPC(SDL_Renderer* des);


	void MoveTo(int x_pos, int y_pos, Map game_map, SmartMap& map_smart);
	void Move(Map& game_map, SmartMap& map_smart);
	void Set_Clip();
	
	void MoveMapForNPC(Map& game_map);
	void Go();
	void Re(int a);

	void NumberTurn(SmartMap& map_smart);
	

	bool LuaTheo(int x, int y, Map& game_map);
	
	

	bool LoseNPC(int x, int y);
	

private:

	
	int x_pos_;
	int y_pos_;

	int x_pos_vir_;
	int y_pos_vir_;

	int map_x_;
	int map_y_;


	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[SIZENPC];
	int frame_;
	
	Input input_type_;

	vector <int> kieure;

	int x_end_;
	int y_end_;


	string name_frame_;
	int npc_pos_;
};

