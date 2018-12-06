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
class Background;
class Display
{
    private:
        int resX;
        int resY;
		Camera *camera;
        SDL_Window* window;
		SDL_Surface* surface;

		int rectAmount = 0;

		//BUG
		//For some reason, these arrays "share" elements.
		SDL_Rect rects[255];
		SDL_Rect textRect[255];
		SDL_Rect letterRect[37];
		SDL_Rect scoreRect;
		SDL_Rect buttonRect = { 0,0,0,0 };
		const char* letters = " abcdefghijklmnopqrstuvwxyz0123456789";
		//const char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		TTF_Font *font = NULL;

		struct Message {
			SDL_Rect rects[255];
			int letterIndex[255];
			int messageLength = 0;
		};

		Message messageLog[20];
		Message scoreLog[4];

		struct Box {
			int x = 200;
			int y = 200;
			int w = 50;
			int h = 50;
		};
		Box testBox;

		SDL_Rect consoleRect;

		bool drawConsoleThisFrame = false;

    public:
		Display();
		~Display();
		bool init();
		void close();
		SDL_Renderer* getRenderer();
		SDL_Window* getWindow();
		bool loadTextures(const char* spriteName, int entityID);
		bool LoadFont();
		void PrintText();
		void DrawScore(int score);
		void CreateButton(const int x, const int y, const int w, const int h);
		void update();
		//void setSprite(*Entity);
		void draw(Entity*);
		//draw individuals
		//void draw(World::horizontal*);
		void draw(World*);
		void draw(Hud*);
		void draw(Background* background);
		void draw(const int x, const int y, const int w, const int h);
		void GameOver();
		int getResX();
		int getResY();
		void render();
		void SetCamera(Camera* camera);
		SDL_Rect srcrect[255];
		SDL_Rect dstrect[255];
		SDL_Renderer* renderer;
		SDL_Texture* entityTexture[255];
		SDL_Texture* fontTexture;
		SDL_Texture* letterTextures[37];

		void DrawConsole();
};

#endif
