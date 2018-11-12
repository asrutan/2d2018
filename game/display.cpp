//display.cpp
//Alex Rutan / PA
//11/22/15

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>
#include "display.h"
#include "hud.h"
#include "console.h"

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

	rects[0].x = testBox.x;
	rects[0].y = testBox.y;
	rects[0].w = testBox.w;
	rects[0].h = testBox.h;

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
				else {
					if (!LoadFont()) {
						success = false;
					}
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

	SDL_DestroyTexture(fontTexture);
	fontTexture = NULL;

	if (!font) {
		TTF_CloseFont(font);
		font = NULL;
	}

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

bool Display::LoadFont()
{

	//Loading success flag 
	bool success = true; 
	//Open the font 
	font = TTF_OpenFont( "Basic-Regular.ttf", 28 ); 
	if( font == NULL ) {
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false; 
	}
	else 
	{ //Render text 
		//{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		SDL_Color textColor = { 0, 0, 0 };
		for (int i = 0; i < 26; i++) {
			string sym(1, letters[i]);
			const char *theval = sym.c_str();
			surface = TTF_RenderText_Solid(font,
				theval, textColor);

			letterTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
			int textW = 0;
			int textH = 0;
			SDL_QueryTexture(letterTextures[i], NULL, NULL, &textW, &textH);
			letterRect[i] = { 0, 0, textW, textH };
		}
	}
	return success;
}

//Don't do this every frame.
void Display::PrintText()
{
	for (int i = 0; i < messageLog[0].messageLength; i++) {
		SDL_RenderCopy(renderer, letterTextures[messageLog[0].letterIndex[i]], NULL, &messageLog[0].rects[i]);
	}
}

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
	dstrect[entity->getEntityID()].x = entity->x - camera->x;
	dstrect[entity->getEntityID()].y = entity->y - camera->y;
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

	if (entity->rotating) {
		SDL_RenderCopyEx(renderer, entityTexture[entity->getEntityID()], NULL, &dstrect[entity->getEntityID()], entity->angle, NULL, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopy(renderer, entityTexture[entity->getEntityID()], NULL, &dstrect[entity->getEntityID()]); //draw entity
	}
}

void Display::draw(World *world)
{
	int camX = camera->x;
	int camY = camera->y;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

	SDL_RenderDrawLine(
		renderer,
		world->horizonts[0]->x1 - camX, 
		world->horizonts[0]->y - camY,
		world->horizonts[0]->x2 - camX, 
		world->horizonts[0]->y - camY
	);

	SDL_RenderDrawLine(
		renderer, 
		world->verts[0]->x - camX, 
		world->verts[0]->y1 - camY, 
		world->verts[0]->x - camX, 
		world->verts[0]->y2 - camY
	);

	SDL_RenderDrawLine(
		renderer,
		world->verts[1]->x - camX,
		world->verts[1]->y1 - camY,
		world->verts[1]->x - camX,
		world->verts[1]->y2 - camY
	);

	for (int i = 0; i < world->brushCount; i++) {
		rects[i].x = world->brushes[i]->x - camX;
		rects[i].y = world->brushes[i]->y - camY;
		rects[i].w = world->brushes[i]->w;
		rects[i].h = world->brushes[i]->h;

		//rects[i].x = testBox.x - camX;
		//rects[i].y = testBox.y - camY;

		//wont work here
		SDL_SetRenderDrawColor(
			renderer,
			world->brushes[i]->color[0],
			world->brushes[i]->color[1],
			world->brushes[i]->color[2],
			world->brushes[i]->color[3]
		);
	}

	SDL_RenderDrawRects(
		renderer,
		rects,
		world->brushCount
	);
	/*
	SDL_RenderFillRect(
		renderer,
		rects
	);
	*/
}

void Display::draw(Hud *hud)
{
	cout << hud->GetElementString(0) << endl;
}

void Display::GameOver()
{
	SDL_UpdateWindowSurface(window);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //background fill 
	SDL_RenderClear(renderer);
	render();
}

void Display::render()
{
	//Test render text
	//SDL_RenderCopy(renderer, fontTexture, NULL, &textRect[0]);
	PrintText();

	//SDL_RenderCopy(renderer, letterTextures[messageLog[0].letterIndex[2]], NULL, messageLog[0].rects);

	SDL_RenderPresent(renderer);	//This updates the screen with what has been drawn on the renderer

}

void Display::SetCamPtr(Camera *Camera)
{
	camera = Camera;
}

void Display::DrawConsole()
{
	//printf("Console message: %s \n", console.GetMessage());
	//PrintText(console.GetMessage());

	const char* text = console.GetMessage();

	//Clear message.
	for (int i = 0; i++; i < 20) {
		messageLog[i].letterIndex[i] = 0;
		messageLog[i].messageLength = 0;
	}

	int i = 0;
	int pointer = 0;
	const int spacing = 20;
	int messageLength = 0;
	while (text[i] != 0) {
		for (int j = 0; j < 26; j++) {
			if (text[i] == letters[j]) {
				messageLog[0].rects[i] = letterRect[j];
				messageLog[0].rects[i].x = pointer;
				messageLog[0].rects[i].y = 0;
				messageLog[0].letterIndex[i] = j;
				pointer += letterRect[j].w;
				j = 27; //exit for
			}
		}
		i++;
	}

	messageLog[0].messageLength = i;

	//cout << letters[2] << endl;
	//cout << text[4] << endl;
}


