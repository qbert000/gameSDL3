#include "npc.h"

NPC::NPC(int x_pos, int y_pos) {

	x_pos_ = x_pos;
	y_pos_ = y_pos;
	input_type_.right_ = 0;
	input_type_.left_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	input_type_.way_ = 1;

	frame_ = 0;

	x_pos_vir_ = x_pos;
	y_pos_vir_ = y_pos;

	x_end_ = 0;
	y_end_ = 0;

	
	
}

bool NPC::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = BackGround::LoadImg(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w / SIZENPC;
		height_frame_ = rect_.h;
	}
	name_frame_ = path;
	Set_Clip();
	return ret;
}

void NPC::ShowNPC(SDL_Renderer* des) {
	LoadImg(name_frame_, des);
	
	if (input_type_.right_ == 1) {
		frame_ = 6+ (frame_ + 1) % 2;
	}
	else if (input_type_.left_ == 1) {
		frame_ = 4 + (frame_ + 1) % 2;
	}
	else if (input_type_.up_ == 1) {
		frame_ =  (frame_ + 1) % 2;
	}
	else {
		frame_ = 2 + (frame_ + 1) % 2;
	}
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { x_pos_ - map_x_ , y_pos_ - map_y_, width_frame_, height_frame_ };
	SDL_RenderCopy(des, p_project_, current_clip, &renderQuad);
}

void NPC::Set_Clip() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < SIZENPC; i++) {
			if (i == 0) {
				frame_clip_[i].x = 0;
			}
			else {
				frame_clip_[i].x = frame_clip_[i - 1].x + width_frame_;
			}
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void NPC::MoveMapForNPC(Map& game_map) {
	game_map.now_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (game_map.now_x_ < 0) game_map.now_x_ = 0;
	else if (game_map.now_x_ + SCREEN_WIDTH >= game_map.max_x_) game_map.now_x_ = game_map.max_x_ - SCREEN_WIDTH;

	game_map.now_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (game_map.now_y_ < 0) game_map.now_y_ = 0;
	else if (game_map.now_y_ + SCREEN_HEIGHT >= game_map.max_y_) game_map.now_y_ = game_map.max_y_ - SCREEN_HEIGHT;
}

void NPC::MoveTo(int x_pos, int y_pos, Map game_map, SmartMap& map_smart) {

	int k;

	if ((y_pos % SIZE_PIXEL != 0 || x_pos % SIZE_PIXEL != 0) ) {//y_pos % SIZE_PIXEL != 0 || x_pos % SIZE_PIXEL != 0
		return;
	}


	else
	npc_pos_ = game_map.pixel_map_[y_pos / SIZE_PIXEL][x_pos / SIZE_PIXEL];

	switch (npc_pos_) {
	case 14: 
		input_type_.down_ = 1;
		input_type_.up_ = 0;
		input_type_.right_ = 0;
		input_type_.left_ = 0;
		input_type_.way_ = 0;
		break;
	case 13:
		input_type_.up_ = 1;
		input_type_.down_ = 0;
		input_type_.right_ = 0;
		input_type_.left_ = 0;
		input_type_.way_ = 0;
		break;
	case 11:
		input_type_.right_ = 1;
		input_type_.left_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
		input_type_.way_ = 0;
		break;
	case 12:
		input_type_.left_ = 1;
		input_type_.right_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
		input_type_.way_ = 0;
		break;
	case 1:
		k = input_type_.up_;
		input_type_.up_ = (input_type_.down_ + 1) % 2;
		input_type_.down_ = (k + 1) % 2;	
		input_type_.left_ = 0;
		input_type_.right_ = 0;
		input_type_.way_ = 1;
		break;
	case 0:
		k = input_type_.left_;
		input_type_.left_ = (input_type_.right_ + 1) % 2;
		input_type_.right_ = (k + 1) % 2;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
		input_type_.way_ = 1;
		break;
	case 8:
		input_type_.right_ = (input_type_.left_ + 1) % 2;
		input_type_.down_ = (input_type_.up_ + 1) % 2;
		input_type_.up_ = 0;
		input_type_.left_ = 0;
		input_type_.way_ = 1;
		break;
	case 2:
		input_type_.left_ = (input_type_.right_ + 1) % 2;
		input_type_.down_ = (input_type_.up_ + 1) % 2;
		input_type_.right_ = 0;
		input_type_.up_ = 0;
		input_type_.way_ = 1;
		break;
	case 3:
		input_type_.up_ = (input_type_.down_ + 1) % 2;
		input_type_.left_ = (input_type_.right_ + 1) % 2;
		input_type_.down_ = 0;
		input_type_.right_ = 0;
		input_type_.way_ = 1;
		break;
	case 9:
		input_type_.up_ = (input_type_.down_ + 1) % 2;
		input_type_.right_ = (input_type_.left_ + 1) % 2;
		input_type_.left_ = 0;
		input_type_.down_ = 0;
		input_type_.way_ = 1;
		break;
	case 4:
		NumberTurn(map_smart);
		k = input_type_.left_;
		input_type_.left_ = (input_type_.right_ + 1) % 2;
		input_type_.right_ = (k + 1) % 2;
		input_type_.down_ = (input_type_.up_ + 1) % 2;
		input_type_.up_= 0;
		input_type_.way_ = 2;
		break;
	case 5:
		NumberTurn(map_smart);
		k = input_type_.left_;
		input_type_.left_ = (input_type_.right_ + 1) % 2;
		input_type_.up_ = (input_type_.down_ + 1) % 2;
		input_type_.right_= (k + 1) % 2;
		input_type_.down_ = 0;
		input_type_.way_ = 2;
		break;
	case 6:
		NumberTurn(map_smart);
		k = input_type_.up_;
		input_type_.right_ = (input_type_.left_ + 1) % 2;
		input_type_.up_ = (input_type_.down_ + 1) % 2;
		input_type_.down_ = (k + 1) % 2;
		input_type_.left_ = 0;
		input_type_.way_ = 2;
		break;
	case 7:
		NumberTurn(map_smart);
		k = input_type_.up_;
		input_type_.up_ = (input_type_.down_ + 1) % 2;
		input_type_.down_ = (k + 1) % 2;
		input_type_.left_ = (input_type_.right_ + 1) % 2;
		input_type_.right_ = 0;
		input_type_.way_ = 2;
		break;
	}


	if (input_type_.Sum() > 1) {
		kieure.clear();
		if (input_type_.right_ == 1) {
			kieure.push_back(0);
		}
		if (input_type_.up_ == 1) {
			kieure.push_back(1);
		}
		if (input_type_.left_ == 1) {
			kieure.push_back(2);
		}
		if (input_type_.down_ == 1) {
			kieure.push_back(3);
		}
	}
}

void NPC::Re(int a) {
	if (a == 0) {
		input_type_.right_ = 1;
		input_type_.left_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
	}
	else if (a == 1) {
		input_type_.up_ = 1;
		input_type_.down_ = 0;
		input_type_.right_ = 0;
		input_type_.left_ = 0;
	}
	else if (a == 2) {
		input_type_.left_ = 1;
		input_type_.right_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
	}
	else if (a == 3) {
		input_type_.down_ = 1;
		input_type_.up_ = 0;
		input_type_.right_ = 0;
		input_type_.left_ = 0;
	}
}

/*
void NPC::NpcVirtualMove(int x_end, int y_end, Map& game_map) {

	if (x_pos_/ SIZE_PIXEL == x_end/SIZE_PIXEL && y_pos_/SIZE_PIXEL == y_end/SIZE_PIXEL) {
		x_end_ = x_end;
		y_end_ = y_end;
		input_type_.right_ = 0;
		input_type_.left_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
		return;
	}
	else{
		MoveTo(x_pos_, y_pos_,game_map);
		if (lane_.cross_ == 0 || divong()) {
			a();
		}
		else if (input_type_.Sum() > 1) {
			pos_.x_postion_ = x_pos_;
			pos_.y_postion_ = y_pos_;
			pos_.nhore_ = kieure;
			lane_.lane_to_.push_back(pos_);
			Re(lane_.lane_to_[lane_.lane_to_.size() - 1].nhore_[lane_.lane_to_[lane_.lane_to_.size() - 1].i++]);
		}
		else if (lane_.cross_ == 1) {
			if (input_type_.right_ == 1) x_pos_ += SIZE_PIXEL;
			else if (input_type_.up_ == 1) y_pos_ -= SIZE_PIXEL;
			else if (input_type_.left_ == 1) x_pos_ -= SIZE_PIXEL;
			else if (input_type_.down_ == 1) y_pos_ += SIZE_PIXEL;



		}
		//SDL_Delay(0);

		return NpcVirtualMove(x_end, y_end, game_map);
	}
}

bool NPC::Motion(int x_end, int y_end) {
	if (x_end_ / SIZE_PIXEL == x_end / SIZE_PIXEL && y_end_ / SIZE_PIXEL == y_end / SIZE_PIXEL) {
		return false;
	}
	else {
		ClearLane();
		x_pos_ = (x_pos_vir_/SIZE_PIXEL)*SIZE_PIXEL;
		y_pos_ = (y_pos_vir_/SIZE_PIXEL)*SIZE_PIXEL;
		input_type_.right_ = 0;
		input_type_.left_ = 0;
		input_type_.down_ = 0;
		input_type_.up_ = 0;
		return true;
	}
}

void NPC::a() {
	if (lane_.lane_to_[lane_.lane_to_.size() - 1].i == lane_.lane_to_[lane_.lane_to_.size() - 1].nhore_.size()) {
		lane_.lane_to_.pop_back();
		return a();
	}
	else {
		x_pos_ = lane_.lane_to_[lane_.lane_to_.size() - 1].x_postion_;
		y_pos_ = lane_.lane_to_[lane_.lane_to_.size() - 1].y_postion_;
		Re(lane_.lane_to_[lane_.lane_to_.size() - 1].nhore_[lane_.lane_to_[lane_.lane_to_.size() - 1].i++]);
	}
}

bool NPC::divong() {

	for (int i = 0; i < lane_.lane_to_.size(); i++) {
		if (x_pos_ == lane_.lane_to_[i].x_postion_ && y_pos_ == lane_.lane_to_[i].y_postion_ && lane_.lane_to_.size() > 0) {
			if (lane_.lane_to_[i].i == 1) {
				lane_.lane_to_[i].nhore_.pop_back();
			}

			return true;
		}
	}
	return false;
}*/

void NPC::Go() {
	if (input_type_.right_ == 1) x_pos_ += STEP;
	else if (input_type_.up_ == 1) y_pos_ -= STEP;
	else if (input_type_.left_ == 1) x_pos_ -= STEP;
	else if (input_type_.down_ == 1) y_pos_ += STEP;

	x_pos_vir_ = x_pos_ + SIZE_PIXEL - 1;
	y_pos_vir_ = y_pos_ + SIZE_PIXEL - 1;
}

void NPC::NumberTurn(SmartMap& map_smart) {
	if (input_type_.right_ == 1) {
		map_smart.NumberNpc(x_pos_, y_pos_, 2);
	}
	else if (input_type_.up_ == 1) {
		map_smart.NumberNpc(x_pos_, y_pos_, 3);
	}
	else if (input_type_.left_ == 1) {
		map_smart.NumberNpc(x_pos_, y_pos_, 0);
	}
	else if (input_type_.down_ == 1) {
		map_smart.NumberNpc(x_pos_, y_pos_, 1);
	}
	else return;
}

void NPC::Move(Map& game_map, SmartMap& map_smart) {

	MoveTo(x_pos_, y_pos_, game_map,map_smart);


	if (input_type_.Sum() > 1) {
		int a;
		if (kieure.size() == 3) {
			a = map_smart.Specail(x_pos_, y_pos_, kieure[0], kieure[1], kieure[2]);
		}
		else {
			a = map_smart.Compare(x_pos_, y_pos_, kieure[0], kieure[1]);
		}
		
		//int a = rand() % 2;
		Re(a);
		map_smart.NumberNpc(x_pos_, y_pos_, a);

	}

	Go();


}

bool NPC::LoseNPC(int x, int y) {
	int x1 = x + SIZE_PIXEL - 1;
	int y1 = y + SIZE_PIXEL - 1;
	if ((x_pos_ >= x && x_pos_ <= x1 && y_pos_ >= y && y_pos_ <= y1) || (x_pos_vir_ >= x && x_pos_vir_ <= x1 && y_pos_vir_ >= y && y_pos_vir_ <= y1) ) {
		return true;
	}
	//if ((x / SIZE_PIXEL == x_pos_ / SIZE_PIXEL && y / SIZE_PIXEL == y_pos_ / SIZE_PIXEL) || (x / SIZE_PIXEL == x_pos_vir_ / SIZE_PIXEL && y / SIZE_PIXEL == y_pos_vir_ / SIZE_PIXEL)) {
		//return true;
	//}
	else return false;
}

bool NPC::LuaTheo(int x, int y, Map& game_map) {
	x_pos_vir_ = x_pos_;
	y_pos_vir_ = y_pos_;
	int n = 0;
	if (x_pos_ == x) {

		while (true) {
			n = game_map.pixel_map_[y_pos_vir_ / SIZE_PIXEL][x_pos_vir_ / SIZE_PIXEL];
			if (n != 0) return false;
			y_pos_vir_ += (y - y_pos_) / (abs(y - y_pos_)) * SIZE_PIXEL;
			if (x_pos_vir_ == x) return true;
		}
	}
	else if (y_pos_ == y) {

		while (true) {
			n = game_map.pixel_map_[y_pos_vir_ / SIZE_PIXEL][x_pos_vir_ / SIZE_PIXEL];
			if (n != 0) return false;
			x_pos_vir_ += (x - x_pos_) / (abs(x - x_pos_)) * SIZE_PIXEL;
			if (y_pos_vir_ == y) return true;
		}
	}

	else return false;
}

