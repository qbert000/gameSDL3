#include "fire.h"

Fire::Fire(int x, int y) {
	x_pos_ = x;
	y_pos_ = y;
}

bool Fire::DeleteBackGround(string path, SDL_Renderer* screen) {
	SDL_Texture* new_texture_ = NULL;

	SDL_Surface* new_surface_ = IMG_Load(path.c_str());
	if (new_surface_ != NULL) {
		SDL_SetColorKey(new_surface_, SDL_TRUE, SDL_MapRGB(new_surface_->format, 8, 8, 8));
		new_texture_ = SDL_CreateTextureFromSurface(screen, new_surface_);
		if (new_texture_ != NULL) {
			rect_.h = new_surface_->h;
			rect_.w = new_surface_->w;
		}
	}
	SDL_FreeSurface(new_surface_);
	p_project_ = new_texture_;
	return p_project_ != NULL;
}

bool Fire::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = DeleteBackGround(path, screen);
	if (ret == true) {
		width_frame_ = rect_.w / SIZEFIRE;
		height_frame_ = rect_.h;
	}
	name_frame_ = path;
	Set_Clip();
	return ret;
}

void Fire::Set_Clip() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < SIZEFIRE; i++) {
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

void Fire::ShowFire(SDL_Renderer* des) {
	LoadImg(name_frame_, des);

	frame_ = (frame_ + 1) % SIZEFIRE;
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect renderQuad = { x_pos_ - map_x_ , y_pos_ - map_y_, width_frame_, height_frame_ };
	SDL_RenderCopy(des, p_project_, current_clip, &renderQuad);
}