// texture.cpp
// Alex Rutan / PA
// 11/22/15
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <cmath>
#include "display.h"
#include "texture.h"

using namespace std;

Texture::Texture()
{
    //Not used
    surface = NULL;
    texture = NULL;
}

Texture::~Texture()
{
} //end destructor

bool Texture::makeTexture(string path)
{
    bool success = true;
    surface = IMG_Load(path.c_str());
    if(surface == NULL)
    {
        cout << "Couldn't load " << path.c_str() << endl;
	cout << IMG_GetError() << endl;
	success = false;
    } //end if
    else
    {
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0));
        //surface = IMG_LoadPNG(path.c_str());
	//texture = SDL_CreateTextureFromSurface(display->getRenderer(), surface);
	if(texture == NULL)
	{
	    cout << "Failed to create Texture" << endl;
  	    cout << SDL_GetError() << endl;
	    success = false;
	} //end if
    } //end else
    //cout << success << endl;
    return success;
} //end loadTextures

SDL_Texture* Texture::getTexture()
{
    return texture;
}

