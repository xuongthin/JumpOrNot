
#ifndef OBJECT_H_
#define OBJECT_H_

#include "Global.h"

class Object
{
public:
	Object();
	~Object();
	// void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip);
	void Free();
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};
#endif // !OBJECT_H_
