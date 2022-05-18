#ifndef function_h
#define function_h

#include <iostream>
#include <vector>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string.h>
using namespace std;


//screen
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

#define SCREEN_BPP 32

#define SIZE_PIXEL 50

#define MAX_MAP_X 20
#define MAX_MAP_Y 20

#define MAX_TYPE_PIXEL 20

#define STEP 10

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 0;
const int COLOR_KEY_B = 0;
const int RENDER_DRAW_COLOR = 0xff;

typedef struct Input {
	int left_;
	int right_;
	int up_;
	int down_;
	//bool status_;

	int Sum() {
		return left_ + right_ + up_ + down_;
	}
	void print() {
		cout << right_ << " " << up_ << " " << left_ << " " << down_ << endl;
	}
	int way_;

}Input;

typedef struct Status {
	bool right_;
	bool left_;
	bool down_;
	bool up_;
	bool horizontal_;
	bool vertical_;
	bool freeze_;

}Status;


typedef struct Map {
	int now_x_;
	int now_y_;

	int max_x_;
	int max_y_;

	int pixel_map_[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name_;
}Map;

typedef struct Postion {
	
	int number_turn_[4];
	int gate_[4];
	bool cross;
	
}Postion;

typedef struct Lane {
	int cross_;
	//vector <Position> lane_to_;
}Lane;








#endif // !fanction_h


