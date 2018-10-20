//dispay.h
//Alex Rutan / PA
//11/22/15

#ifndef DISPLAY_EXIST
#define DISPLAY_EXIST

#include <SDL.h>
#include "entity.h"
#include "world.h"
#include <iostream>

class Display
{
    private:
        int resX;
        int resY;
        SDL_Window* window;
		SDL_Surface* surface;

    public:
		Display();
		~Display();
		bool init();
		void close();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();
		bool loadTextures(const char* spriteName, int entityID);
		void update();
		//void setSprite(*Entity);
		void draw(Entity*);
		//draw individuals
		//void draw(World::horizontal*);
		void draw(World*);
		int getResX();
		int getResY();
		void render();
		SDL_Rect srcrect[255];
		SDL_Rect dstrect[255];
		SDL_Renderer* renderer;
		SDL_Texture* entityTexture[255];
};

#endif
