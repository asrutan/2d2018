//display.cpp
//Alex Rutan / PA
//11/22/15

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>
#include "display.h"

using namespace std;

Display::Display()
{
    resX = 800;
    resY = 600;
    window = NULL;
    surface = NULL;
	renderer = NULL;
	for (int i = 0; i < 255; i++)
	{
		entityTexture[i] = NULL;
	}
}//end constructor

Display::~Display()
{
	close();
}//end deconstructor


/*
Initializes SDL and creates window, renderer, and assigns values for their initialization
Has checks to make sure everythin initializes properly
wiOtherwise it would be very hard to pinpoint what is breaking when nothing happens
*/

bool Display::init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL broke or something." << endl;
		success = false;
	} //end if
	else
	{
		window = SDL_CreateWindow("Kawaii", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window Can't Be Created Fool" << endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //present vsync caps framerate at monitor refresh rate, in most cases 60hz so 60 fps
			if (!renderer)
			{
				cout << "Couldn't create window :( " << endl;
				cout << SDL_GetError() << endl;
				success = false;
			} //end if
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError() << endl;
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << endl;
					success = false;
				}
				return success;
			}
		}
	}
}//end init

void Display::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

	SDL_DestroyTexture(*entityTexture);
	*entityTexture = NULL;

    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

SDL_Renderer* Display::getRenderer()
{
    return renderer;
}

SDL_Window* Display::getWindow()
{
    return window;
}

bool Display::loadTextures(const char *spriteName, int entityID)
{
    bool success = true;
	surface = SDL_LoadBMP(spriteName);
    if(surface == NULL)
	{
		cout << "Surface couldn't initialize!" << endl;
		success = false;
	}

	if (surface == NULL)
	{
		printf("Couldn't load textures sry :(");
		cout << SDL_GetError() << endl;
		success = false;
	} //end if
	else
	{
		entityTexture[entityID] = SDL_CreateTextureFromSurface(renderer, surface);
		if (entityTexture[entityID] == NULL)
		{
			success = false;
			cout << "adfdafaf" << endl;
			return success;
		}
		if (entityID == 0) 
		{
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 0;
			srcrect[entityID].h = 0;
			dstrect[entityID].w = 95;
			dstrect[entityID].h = 128;
		}
		else if (entityID == 1)
		{
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 0;
			srcrect[entityID].h = 0;
			dstrect[entityID].w = 50;
			dstrect[entityID].h = 50;
		}
	} //end else
	surface = NULL;
    return success;
} //end loadTextures 

int Display::getResX()
{
    return resX;
}//end getResX

int Display::getResY()
{
    return resY;
}

void Display::update()
{
	SDL_UpdateWindowSurface(window);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //background fill 
	SDL_RenderClear(renderer);
}

//void Display::setSprite(Entity entity)
//{
//}

void Display::draw(Entity *entity)
{
	dstrect[entity->getEntityID()].x = entity->x;
	dstrect[entity->getEntityID()].y = entity->y;
	dstrect[entity->getEntityID()].w = entity->width;
	dstrect[entity->getEntityID()].h = entity->height;

	//SDL_Rect fillRect = {50, 50, 50, 50 };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderFillRect(renderer, &fillRect);

	SDL_RenderDrawPoint(renderer, 700, 500);
	SDL_RenderDrawPoint(renderer, 700, 550);
	SDL_RenderDrawPoint(renderer, 750, 500);
	SDL_RenderDrawPoint(renderer, 750, 550);

	//SDL_RenderCopy(renderer, entityTexture[entity->entityID], &srcrect[entity->entityID], &dstrect[entity->entityID]);

	SDL_RenderCopy(renderer, entityTexture[entity->getEntityID()], NULL, &dstrect[entity->getEntityID()]); //draw entity
}

void Display::draw(World *world)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

	SDL_RenderDrawLine(renderer, world->horizonts[0]->x1, world->horizonts[0]->y, world->horizonts[0]->x2, world->horizonts[0]->y);
	SDL_RenderDrawLine(renderer, world->verts[0]->x, world->verts[0]->y1, world->verts[0]->x, world->verts[0]->y2);
	SDL_RenderDrawLine(renderer, world->verts[1]->x, world->verts[1]->y1, world->verts[1]->x, world->verts[1]->y2);
}

void Display::render()
{
	SDL_RenderPresent(renderer);	//This updates the screen with what has been drawn on the renderer
}