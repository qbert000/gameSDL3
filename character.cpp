#include"character.h"

Character::Character() {
	x_pos_ = SIZE_PIXEL*0;
	y_pos_ = SIZE_PIXEL*19;

	x_pos_old_ = x_pos_;
	y_pos_old_ = y_pos_;

	width_frame_ = 0;
	height_frame_ = 0;

	x_val_ = 0;
	y_val_ = 0;

	frame_ = 0;
	turn_ = false;
	goThrought_ = false;

	input_type_.right_ = 0;
	input_type_.left_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;

	status_.vertical_ = false;
	status_.horizontal_ = false;
	

}

Character:: ~Character() {

}

bool Character::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = BackGround::LoadImg(path, screen);;
	if (ret == true) {
		width_frame_ = rect_.w / SIZECHAR;
		height_frame_ = rect_.h;
	}
	Set_Clip();
	return ret;
}

void Character::Show(SDL_Renderer* des) {
	LoadImg("img//pacnu.png", des);

	if (status_.freeze_ ) {
		frame_ = (frame_ + 1) % SIZECHAR;
	}
	else { 
		frame_ = 2; 
	}

	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { x_pos_ - map_x_, y_pos_ - map_y_, width_frame_, height_frame_ };

	if (status_.horizontal_) {
		if (input_type_.left_ == 1) {
			SDL_RenderCopy(des, p_project_, current_clip, &renderQuad);
		}
		else if(input_type_.right_ == 1) {
			SDL_RenderCopyEx(des, p_project_, current_clip, &renderQuad, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
	else if (status_.vertical_) {
		if (input_type_.up_ == 1) {
			SDL_RenderCopyEx(des, p_project_, current_clip, &renderQuad, 90, NULL, SDL_FLIP_NONE);
		}
		else if (input_type_.down_ == 1) { 
			SDL_RenderCopyEx(des, p_project_, current_clip, &renderQuad, -90, NULL, SDL_FLIP_NONE);
		}
	}else SDL_RenderCopy(des, p_project_, current_clip, &renderQuad);

	
}

void Character::Set_Clip() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < SIZECHAR; i++) {
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

void Character::Move(SDL_Event event) {
	
	

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_d:
			
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			if (status_.horizontal_) {
				input_type_.down_ = 0;
				input_type_.up_ = 0;
			}
			break;
		case SDLK_a:
			
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			if (status_.horizontal_) {
				input_type_.down_ = 0;
				input_type_.up_ = 0;
			}
			break;
		case SDLK_w:
			
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			if (status_.vertical_) {
				input_type_.right_ = 0;
				input_type_.left_ = 0;
			}
			break;
		case SDLK_s:
			
			input_type_.down_ = 1;
			input_type_.up_ = 0;
			if (status_.vertical_) {
				input_type_.right_ = 0;
				input_type_.left_ = 0;
			}
			break;
		}
	}

	/*if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_d:
			
			input_type_.right_ = 0;
			break;
		case SDLK_a:
			
			input_type_.left_ = 0;
			break;
		case SDLK_w:
			
			input_type_.up_ = 0;
			break;
		case SDLK_s:
			
			input_type_.down_ = 0;
			break;
		}
	}*/
	
	status_.freeze_ = true;
}

void Character::Turn(Map& game_map) {
	MoveTo(game_map);
	if ((input_type_.up_ == 1 && status_.up_ == true) || (input_type_.down_ == 1 && status_.down_ == true)) {
		input_type_.right_ = 0;
		input_type_.left_ = 0;
		status_.right_ = false;
		status_.left_ = false;
		status_.up_ = false;
		status_.down_ = false;
		status_.horizontal_ = false;
		
	}
	else if ((input_type_.right_ == 1 && status_.right_ == true) || (input_type_.left_ == 1 && status_.left_ == true)) {
		input_type_.up_ = 0;
		input_type_.down_ = 0;
		status_.right_ = false;
		status_.left_ = false;
		status_.up_ = false;
		status_.down_ = false;
		status_.vertical_ = false;
	}
	else return;
	
}

void Character::Go(Map& game_map, SmartMap& map_smart) {
	
	pos_ = game_map.pixel_map_[y_pos_ / SIZE_PIXEL][x_pos_ / SIZE_PIXEL];

	
	turn_ = true;

	x_val_ = x_pos_;
	y_val_ = y_pos_;

	Turn(game_map);

	if (input_type_.right_ == 1) x_pos_ += STEP;
	else if (input_type_.left_ == 1) x_pos_ -= STEP;
	MoveForMap(game_map);

	if (turn_) {
		if (input_type_.down_ == 1) y_pos_ += STEP;
		else if (input_type_.up_ == 1) y_pos_ -= STEP;
		MoveForMap(game_map);
	}
	
	if (x_pos_ == x_val_ && y_pos_ == y_val_) {
		status_.freeze_ = false;
	}

	StatusCharacter();

	Downnumber(map_smart);

	Upnumber(map_smart);
	
	SDL_Delay(50);
}

void Character::StatusCharacter() {
	if (input_type_.right_ == 1 || input_type_.left_ == 1) {
		if (status_.vertical_) {
			status_.horizontal_ = false;
		}
		else status_.horizontal_ = true;
	}
	if (input_type_.up_ == 1 || input_type_.down_ == 1) {
		if (status_.horizontal_) {
			status_.vertical_ = false;
		}
		else status_.vertical_ = true;
	}
}

void Character::MoveMapForCharacter(Map& game_map) {
	game_map.now_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (game_map.now_x_ < 0) game_map.now_x_ = 0;
	else if (game_map.now_x_ + SCREEN_WIDTH >= game_map.max_x_) game_map.now_x_ = game_map.max_x_ - SCREEN_WIDTH;

	game_map.now_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (game_map.now_y_ < 0) game_map.now_y_ = 0;
	else if (game_map.now_y_ + SCREEN_HEIGHT >= game_map.max_y_) game_map.now_y_ = game_map.max_y_ - SCREEN_HEIGHT;
}

void Character::MoveForMap(Map game_map) {

	
	int x_pos_virtual_ = x_pos_ + SIZE_PIXEL-1;
	int y_pos_virtual_ = y_pos_ + SIZE_PIXEL -1;
	
	
	if (x_pos_virtual_ / SIZE_PIXEL - x_pos_ / SIZE_PIXEL + y_pos_virtual_ / SIZE_PIXEL - y_pos_ / SIZE_PIXEL == 2) {
		x_pos_ = x_pos_old_;
		y_pos_ = y_pos_old_;
		return;
	}
	
	int x_pos_mae_ = (x_pos_old_ / SIZE_PIXEL)* SIZE_PIXEL;
	int x_pos_ushiro_ = (x_pos_old_ / SIZE_PIXEL + 1) * SIZE_PIXEL;

	int y_pos_ue_ = (y_pos_old_ / SIZE_PIXEL) * SIZE_PIXEL;
	int y_pos_shita_ = (y_pos_old_ / SIZE_PIXEL + 1) * SIZE_PIXEL;

	switch (pos_) {
	case 0:
		y_pos_ = y_pos_old_;
		break;
	case 1:
		x_pos_ = x_pos_old_;
		break;
	case 2:
		x_pos_ = x_pos_ + SIZE_PIXEL > x_pos_ushiro_ ? x_pos_old_ : x_pos_;
		y_pos_ = y_pos_ < y_pos_ue_ ? y_pos_old_ : y_pos_;
		break;
	case 3:
		x_pos_ = x_pos_ + SIZE_PIXEL > x_pos_ushiro_ ? x_pos_old_ : x_pos_;
		y_pos_ = y_pos_ + SIZE_PIXEL > y_pos_shita_ ? y_pos_old_ : y_pos_;
		break;
	case 4:
		y_pos_ = y_pos_ < y_pos_ue_ ? y_pos_old_ : y_pos_;
		break;
	case 5:
		y_pos_ = y_pos_ + SIZE_PIXEL > y_pos_shita_ ? y_pos_old_ : y_pos_;
		break;
	case 6:
		x_pos_ = x_pos_ < x_pos_mae_ ? x_pos_old_ : x_pos_;
		break;
	case 7:
		x_pos_ = x_pos_ + SIZE_PIXEL > x_pos_ushiro_ ? x_pos_old_ : x_pos_;
		break;
	case 8:
		x_pos_ = x_pos_ < x_pos_mae_ ? x_pos_old_ : x_pos_;
		y_pos_ = y_pos_ < y_pos_ue_ ? y_pos_old_ : y_pos_;
		break;
	case 9:
		x_pos_ = x_pos_ < x_pos_mae_ ? x_pos_old_ : x_pos_;
		y_pos_ = y_pos_ + SIZE_PIXEL > y_pos_shita_ ? y_pos_old_ : y_pos_;
		break;
	case 11:
		y_pos_ = y_pos_old_;
		x_pos_ = x_pos_ < x_pos_mae_ ? x_pos_old_ : x_pos_;
		break;
	case 12:
		y_pos_ = y_pos_old_;
		x_pos_ = x_pos_ + SIZE_PIXEL > x_pos_ushiro_ ? x_pos_old_ : x_pos_;
		break;
	case 13:
		x_pos_ = x_pos_old_;
		y_pos_ = y_pos_ + SIZE_PIXEL > y_pos_shita_ ? y_pos_old_ : y_pos_;
		break;
	case 14:
		x_pos_ = x_pos_old_;
		y_pos_ = y_pos_ < y_pos_ue_ ? y_pos_old_ : y_pos_;
		break;
	}

	


	

	if (x_pos_ != x_pos_old_ && y_pos_ == y_pos_old_) {
		turn_ = false;
	}

	x_pos_old_ = x_pos_;
	y_pos_old_ = y_pos_;

	
	
}

void Character::MoveTo( Map& game_map) {

	if ((y_pos_ % SIZE_PIXEL != 0 || x_pos_ % SIZE_PIXEL != 0)) {//y_pos % SIZE_PIXEL != 0 || x_pos % SIZE_PIXEL != 0
		status_.right_ = false;
		status_.left_ = false;
		status_.up_ = false;
		status_.down_ = false;
		return;
	}


	else
		//pos_ = game_map.pixel_map_[y_pos_ / SIZE_PIXEL][x_pos_ / SIZE_PIXEL];

	switch (pos_) {
	
	
	case 8:
		status_.right_ = true;
		status_.up_ = false;
		status_.left_ = false;
		status_.down_ = true;
		break;
	case 2:
		status_.right_ = false;
		status_.up_ = false;
		status_.left_ = true;
		status_.down_ = true;
		break;
	case 3:
		status_.right_ = false;
		status_.up_ = true;
		status_.left_ = true;
		status_.down_ = false;
		break;
	case 9:
		status_.right_ = true;
		status_.up_ = true;
		status_.left_ = false;
		status_.down_ = false;
		break;
	case 4:
		status_.down_ = true;
		status_.right_ = status_.horizontal_ == true ? false : true;
		status_.left_ = status_.horizontal_ == true ? false : true;
		status_.up_ = false;
		break;
	case 5:
		status_.down_ = false;
		status_.right_ = status_.horizontal_ == true ? false : true ;
		status_.left_ = status_.horizontal_ == true ? false : true;
		status_.up_ = true; 
		break;
	case 6:
		status_.down_ = status_.vertical_ == true ? false : true;
		status_.right_ = true;
		status_.left_ = false;
		status_.up_ = status_.vertical_ == true ? false : true;
		break;
	case 7:
		status_.down_ = status_.vertical_ == true ? false : true;
		status_.right_ = false;
		status_.left_ = true;
		status_.up_ = status_.vertical_ == true ? false : true;
		break;
	}
}

void Character::Downnumber(SmartMap& map_smart) {
	if (x_val_ % SIZE_PIXEL == 0 && y_val_ % SIZE_PIXEL == 0) {
		if (pos_ == 4 || pos_ == 5 || pos_ == 6 || pos_ == 7) {
			if (x_val_ < x_pos_) {
				map_smart.DownChar(x_val_, y_val_, 0);
			}
			else if (x_val_ > x_pos_) {
				map_smart.DownChar(x_val_, y_val_, 2);
			}
			else if (y_val_ > y_pos_) {
				map_smart.DownChar(x_val_, y_val_, 1);
			}
			else if (y_val_ < y_pos_) {
				map_smart.DownChar(x_val_, y_val_, 3);
			}
			else {
				return;
			}
			//map_smart.CoutMap(x_val_, y_val_);
		}
	}
}

void Character::Upnumber(SmartMap& map_smart) {
	if (goThrought_ && x_pos_ % SIZE_PIXEL == 0 && y_pos_ % SIZE_PIXEL == 0) {
		if (status_.horizontal_) {
			if (input_type_.right_ == 1) {
				map_smart.NumberNpc(x_pos_, y_pos_, 2);
			}
			else if (input_type_.left_ == 1) {
				map_smart.NumberNpc(x_pos_, y_pos_, 0);
			}
		}
		if (status_.vertical_) {
			if (input_type_.up_) {
				map_smart.NumberNpc(x_pos_, y_pos_, 3);
			}
			else if (input_type_.down_ == 1) {
				map_smart.NumberNpc(x_pos_, y_pos_, 1);
			}
		}
		//map_smart.CoutMap(x_pos_, y_pos_);
	}
	Dosomething();
}


void Character::Dosomething() {
	if (x_pos_ % SIZE_PIXEL != 0 || y_pos_ % SIZE_PIXEL != 0) {
		goThrought_ = true;
	}
	else {
		//if (pos_ == 4 || pos_ == 5 || pos_ == 6 || pos_ == 7) {
		//	goThrought_ = false;
		//}
		//else {
		goThrought_ = false;
		//}
	}
}





void Character::CoutInput() {
	cout << input_type_.Sum();
}

bool Character::WinGame(Map game_map) {
	if (0) return true;
	else return false;
}