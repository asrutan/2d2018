//PA
//textTexture.j
//11/22/15

#ifndef T_TEXTURE_EXIST
#define T_TEXTURE_EXIST

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string.h>
#include "display.h"

class textTexture
{
    private:
        Display* display;
        SDL_Texture* myTexture;
	TTF_Font* textFont;
	int textWidth;
	int textHeight;

    public:
	textTexture();
	textTexture(Display*);
	~textTexture();
	bool loadFontMedia(std::string path);
	bool loadFontFromRenderedText(std::string, SDL_Color);
	void releaseTextTexture();
	void renderTextTexture(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getFontFileWidth();
	int getFontFileHeight();

	
}; //end textTexture

#endif //T_TEXTURE_EXISTS
