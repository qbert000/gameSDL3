#include "SmartMap.h"


SmartMap::SmartMap(Map& game_map) {


	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			int a = game_map.pixel_map_[i][j];
			if (a == 5 || a == 4 || a == 6 || a == 7) {
				map_smart_[i][j].cross = true;
				
			}
			for (int k = 0; k < 4; k++) {
					map_smart_[i][j].number_turn_[k] = 0;
					map_smart_[i][j].gate_[k] = 0;
				}
		}
	}
}

void SmartMap::FollowCharacter(int x, int y) {

	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			if (map_smart_[i][j].cross == true) {
				if (x/SIZE_PIXEL > j) {
					map_smart_[i][j].gate_[0] = 1;
					map_smart_[i][j].gate_[2] = 0;
				}
				else if (x/SIZE_PIXEL < j) {
					map_smart_[i][j].gate_[0] = 0;
					map_smart_[i][j].gate_[2] = 1;
				}
				else {
					map_smart_[i][j].gate_[0] = 0;
					map_smart_[i][j].gate_[2] = 0;
				}

				if (y/SIZE_PIXEL > i) {
					map_smart_[i][j].gate_[3] = 1;
					map_smart_[i][j].gate_[1] = 0;
				}
				else if (y/SIZE_PIXEL < i) {
					map_smart_[i][j].gate_[3] = 0;
					map_smart_[i][j].gate_[1] = 1;
				}
				else {
					map_smart_[i][j].gate_[3] = 0;
					map_smart_[i][j].gate_[1] = 0;
				}

				
			}
		}
	}
}

void SmartMap::NumberNpc(int x, int y, int a) {
	map_smart_[y/SIZE_PIXEL][x/SIZE_PIXEL].number_turn_[a]++;
}

void SmartMap::DownChar(int x, int y, int a) {
	map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[a]--;
}

int SmartMap::Compare(int x, int y, int a1, int a2) {
	//cout << map_smart_[y/SIZE_PIXEL][x/ SIZE_PIXEL].number_turn_[a1] << " " << map_smart_[y/SIZE_PIXEL][x/SIZE_PIXEL].number_turn_[a2] << endl;
	if (map_smart_[y/SIZE_PIXEL][x/SIZE_PIXEL].number_turn_[a1] > map_smart_[y/SIZE_PIXEL][x/SIZE_PIXEL].number_turn_[a2]) {
		return a2;
	}
	else if (map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[a1] < map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[a2]) {
		return a1;
	}
	else {
		if (map_smart_[y/SIZE_PIXEL][x/SIZE_PIXEL].gate_[a1] > map_smart_[y/SIZE_PIXEL][x/SIZE_PIXEL].gate_[a2]) {
			return a1;
		}
		else if (map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].gate_[a1] < map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].gate_[a2]) {
			return a2;
		}
		else {
			int k = rand() % 2;
			if (k == 0) return a1;
			else return a2;
		}
		
		
	}
	
}


void SmartMap::CoutMap(int x, int y) {
	cout << x << " " << y << "     ";
	cout << map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[2] << " " << map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[0];
	cout << "    " << map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[1] << " " << map_smart_[y / SIZE_PIXEL][x / SIZE_PIXEL].number_turn_[3];
	cout << endl;
}
