
#include "Object.h"
#include "Global.h"

Object::Object()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

Object::~Object()
{
	Free();
}

bool Object::LoadImg(std::string path, SDL_Renderer * screen)
{
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOER_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_ = new_texture;

	return p_object_ != NULL;
}

void Object::Render(SDL_Renderer * des, const SDL_Rect* rect_location /* = NULL */)
{
	if (rect_location == NULL)
	{
		SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
		SDL_RenderCopy(des, p_object_, NULL, &renderquad);
	}
	else
	{
		SDL_RenderCopy(des, p_object_, NULL, rect_location);
	}
}

void Object::Free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.h = 0;
		rect_.w = 0;
	}
}
