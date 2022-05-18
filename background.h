#ifndef back_ground_h
#define back_ground_h

#include "function.h"

class BackGround {
public:
	BackGround();
	~BackGround();

	void ChangeRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() { return rect_; };
	SDL_Texture* GetTuxture() { return p_project_; };

	virtual bool LoadImg(string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
protected:
	SDL_Rect rect_;
	SDL_Texture* p_project_;
};











#endif // !back_ground_h

