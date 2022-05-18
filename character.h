#ifndef character_h
#define character_h

#include "background.h"
#include "function.h"
#include "tile_map.h"
#include "SmartMap.h"

#define SIZECHAR 3
class Character: public BackGround {
public:
	Character();
	~Character();
	


	bool LoadImg(string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void SetMapXY(const int map_x, const int map_y) {
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void MoveMapForCharacter(Map& game_map);

	void Upnumber(SmartMap& map_smart);
	void Downnumber(SmartMap& map_smart);
	void Dosomething();

	void Move(SDL_Event event);
	void Go(Map& game_map, SmartMap& map_smart);
	void Turn(Map& game_map);
	void MoveTo(Map& game_map);
	void MoveForMap(Map game_map);
	void StatusCharacter();
	
	
	
	int Getx_Pos() { return x_pos_; };
	int Gety_Pos() { return y_pos_; };
	
	void CoutInput();
	void Set_Clip();
	
	bool WinGame(Map game_map);
private:
	
	int x_pos_;
	int y_pos_;

	int x_pos_old_;
	int y_pos_old_;

	int x_val_;
	int y_val_;

	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[SIZECHAR];
	int frame_;
	
	Input input_type_;
	Status status_;

	int pos_;
	bool turn_;

	bool goThrought_;

	int map_x_;
	int map_y_;
};








#endif // !character_h

