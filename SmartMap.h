#pragma once

#include "function.h"


class SmartMap {
public:
	SmartMap(Map& game_map);
	
	void FollowCharacter(int x, int y);

	void NumberNpc(int x, int y, int a);
	void DownChar(int x, int y, int a);
	int Compare(int x, int y, int a1, int a2);
	void CoutMap(int x, int y);
private:


	Postion map_smart_[MAX_MAP_Y][MAX_MAP_X];


};