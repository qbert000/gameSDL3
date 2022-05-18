#pragma once

#include "function.h"
#include "background.h"
#include "tile_map.h"
#include "character.h"
#include "npc.h"

class NPCVirtual {
public:
	NPCVirtual(int x_pos, int y_pos);
	~NPCVirtual();
	void MoveForMap(Map& game_map);

private:

	int x_pos_;
	int y_pos_;

	Input type_;

	bool status_;

	int k;

};