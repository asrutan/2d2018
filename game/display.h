//dispay.h
//Alex Rutan / PA
//11/22/15

#ifndef DISPLAY_EXIST
#define DISPLAY_EXIST

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "entity.h"
#include "world.h"
#include "camera.h"
#include <iostream>

class Hud;
class Console;

class Display
{
    private:
        int resX;
        int resY;
		Camera *camera;
        SDL_Window* window;
		SDL_Surface* surface;

		//BUG
		//For some reason, these arrays "share" elements.
		SDL_Rect rects[255];
		SDL_Rect textRect[255];

		TTF_Font *font = NULL;

		struct Box {
			int x = 200;
			int y = 200;
			int w = 50;
			int h = 50;
		};
		Box testBox;

    public:
		Display();
		~Display();
		bool init();
		void close();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();
		bool loadTextures(const char* spriteName, int entityID);
		bool LoadFont();
		void update();
		//void setSprite(*Entity);
		void draw(Entity*);
		//draw individuals
		//void draw(World::horizontal*);
		void draw(World*);
		void draw(Hud*);
		void GameOver();
		int getResX();
		int getResY();
		void render();
		void SetCamPtr(Camera*);
		SDL_Rect srcrect[255];
		SDL_Rect dstrect[255];
		SDL_Renderer* renderer;
		SDL_Texture* entityTexture[255];
		SDL_Texture* fontTexture;

		void DrawConsole();
};

#endif
