#include "background.h"

BackGround::BackGround() {
	p_project_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.h = 0;
	rect_.w = 0;
}

BackGround::~BackGround() {

}

bool BackGround::LoadImg(string path, SDL_Renderer* screen) {
	SDL_Texture* new_texture_ = NULL;

	SDL_Surface* new_surface_ = IMG_Load(path.c_str());
	if (new_surface_ != NULL) {
		SDL_SetColorKey(new_surface_, SDL_TRUE, SDL_MapRGB(new_surface_->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
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

void BackGround::Render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_project_, clip, &renderquad);
}

void BackGround::Free() {
	if (p_project_ != NULL) {
		SDL_DestroyTexture(p_project_);
		p_project_ = NULL;
		rect_.h = 0;
		rect_.w = 0;

	}
}


