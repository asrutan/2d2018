// texture.h
// Alex Rutan / PA
// 11/22/15

#ifndef TEXTURE_EXIST
#define TEXTURE_EXIST

#include <SDL.h>
#include <SDL_image.h>
#include <string.h>

class Texture
{
    private:
	//Display* display;
	SDL_Surface* surface;
	SDL_Texture* texture;

    public:
	Texture();
       // Texture(Display*);
        ~Texture();
	bool makeTexture(std::string);
	SDL_Texture* getTexture();
}; //end Texture

#endif //TEXTURE_EXISTS
