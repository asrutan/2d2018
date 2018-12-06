//display.cpp
// PA
//Alex Rutan 
//11/22/15

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>
#include "display.h"
#include "hud.h"
#include "console.h"
#include "background.h"

using namespace std;

/*
===========================Display()===========================
Initialize sdl rectangles, allocate arrays for textures.
===============================================================
*/
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

	/*
	======Console======
	*/
	consoleRect.x = 0;
	consoleRect.y = 0;
	consoleRect.w = 800;
	consoleRect.h = 25;


	/*
	===================
	*/
	//SCORE
	scoreRect.x = 0;
	scoreRect.y = 0;
	scoreRect.w = 25;
	scoreRect.h = 25;
	//
}//end constructor

Display::~Display()
{
	close();
}//end deconstructor


/*
Initializes SDL and creates window, renderer, and assigns values for their initialization
Has checks to make sure everythin initializes properly
Otherwise it would be very hard to pinpoint what is breaking when nothing happens
*/
/*
===========================init()=============================
Create the window and initialize the libraries for display 
text and pictures. Set the window and video modes. Turn on
vertical-sync to prevent screen-tearing and cap the framerate.
===============================================================
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
		window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);
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

/*
===========================close()=============================
Free up every surface, get rid of textures, destroy the renderer.
Quit SDL, TTF, and IMG libraries.
===============================================================
*/
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

/*
===========================loadTextures()======================
Depending on the element, load the appropriate image file and 
convert it to an SDL surface. We use SDL_IMG to load .png files
and maintain their transparency. From there, create an SDL 
Texture from the surface and add it to an array of textures.
Any time we want to draw an object with that texture, just look
at that spot in the array and blit it to the renderer.
===============================================================
*/
bool Display::loadTextures(const char *spriteName, int entityID)
{
    bool success = true;
	//surface = SDL_LoadBMP(spriteName);
	surface = IMG_Load(spriteName);
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
			return success;
		}
		if (entityID == 0) //Player
		{
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 0;
			srcrect[entityID].h = 0;
			dstrect[entityID].w = 114;
			dstrect[entityID].h = 159;
		}
		else if (entityID == 1) //Enemy
		{
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 0;
			srcrect[entityID].h = 0;
			dstrect[entityID].w = 50;
			dstrect[entityID].h = 50;
		}
		else if (entityID == 2) //Background
		{
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 990;
			srcrect[entityID].h = 780;
			dstrect[entityID].w = 990;
			dstrect[entityID].h = 780;
		}
		else if (entityID == 3) { //Menu background
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 990;
			srcrect[entityID].h = 780;
			dstrect[entityID].w = 990;
			dstrect[entityID].h = 780;
		}
		else if (entityID == 4) { //resume button
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 100;
			srcrect[entityID].h = 50;
			dstrect[entityID].w = 100;
			dstrect[entityID].h = 50;
		}
		else if (entityID == 5) { //switch button
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 100;
			srcrect[entityID].h = 50;
			dstrect[entityID].w = 100;
			dstrect[entityID].h = 50;
		}
		else if (entityID == 6) { //quit button
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 100;
			srcrect[entityID].h = 50;
			dstrect[entityID].w = 100;
			dstrect[entityID].h = 50;
		}
		else if (entityID == 7) { //jump button
			srcrect[entityID].x = 0;
			srcrect[entityID].y = 0;
			srcrect[entityID].w = 50;
			srcrect[entityID].h = 50;
			dstrect[entityID].w = 50;
			dstrect[entityID].h = 50;
		}
	} //end else
	surface = NULL;
    return success;
} //end loadTextures 

/*
============================LoadFont()=========================
Using the same approach as loadTextures(), iterate through each
letter of the alphabet, create a texture from surface for it, 
and add it to the array of letter textures. Any time we need
that letter, just look for the nth letter of the alphabet.
===============================================================
*/
bool Display::LoadFont()
{
	//Loading success flag 
	bool success = true; 
	//Open the font 
	font = TTF_OpenFont( "Basic-Regular.ttf", 18 ); 
	if( font == NULL ) {
		printf( "Failed to load font. SDL_ttf Error: %s\n", TTF_GetError() );
		success = false; 
	}
	else 
	{ //Render text 
		//{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		SDL_Color textColor = { 0, 0, 0 };
		for (int i = 0; i < 37; i++) {
			if (i > 26) textColor = { 0, 255, 0 };
			string sym(1, letters[i]);
			const char *theval = sym.c_str();
			surface = TTF_RenderText_Solid(font,
				theval, textColor);

			letterTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
			int textW = 0;
			int textH = 0;
			SDL_QueryTexture(letterTextures[i], NULL, NULL, &textW, &textH);
			letterRect[i] = { 0, 0, textW, textH }; //Makes it so the spacing between letters is appropriate for the width of each letter.
		}
	}
	return success;
}

/*
============================PrintText()========================
For each letter in the message from console, print each letter
using the array of letter textures.
===============================================================
*/
void Display::PrintText()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //white
	SDL_RenderFillRect(renderer, &consoleRect);
	for (int i = 0; i < messageLog[0].messageLength; i++) {
		SDL_RenderCopy(renderer, letterTextures[messageLog[0].letterIndex[i]], NULL, &messageLog[0].rects[i]);
	}
}

void Display::DrawScore(int score)
{
	std:string text = std::to_string(score);
	int pointer = 0;
	int i = 0;
	for (i = 0; i < text.length(); i++) {
		for (int j = 0; j < 37; j++) {
			if (text[i] == letters[j]) {
				scoreLog[0].rects[i] = letterRect[j];
				//messageLog[0].rects[i].x = pointer;
				//messageLog[0].rects[i].y = 0;
				scoreLog[0].letterIndex[i] = j;
				j = 38; //exit for by going over limit
			}
		}
	}
	scoreLog[0].messageLength = i;

	for (int i = 0; i < scoreLog[0].messageLength; i++) {
		scoreLog[0].rects[i].h = 50;
		scoreLog[0].rects[i].w = 25;
		scoreLog[0].rects[i].y = 50;
		scoreLog[0].rects[i].x = (i + 1) * 25;
	}

	for (int i = 0; i < scoreLog[0].messageLength; i++) {
		SDL_RenderCopy(renderer, letterTextures[scoreLog[0].letterIndex[i]], NULL, &scoreLog[0].rects[i]);
	}
}

/*
void Display::CreateButton(const int x, const int y, const int w, const int h)
{
	rects[rectAmount].x = x;
	rects[rectAmount].y = y;
	rects[rectAmount].w = w;
	rects[rectAmount].h = h;
	rectAmount++;
}
*/

int Display::getResX()
{
    return resX;
}//end getResX

int Display::getResY()
{
    return resY;
}

/*
============================Update()===========================
Clear the window and fill it with white.
===============================================================
*/
void Display::update()
{
	SDL_UpdateWindowSurface(window);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //background fill 
	SDL_RenderClear(renderer);
}

//void Display::setSprite(Entity entity)
//{
//}

/*
============================Draw()=============================
Draw an entity using it's location offset by the camera position.
If it is flipped or rotating, use RenderCopyEx, otherwise just
use RenderCopy to put the texture on the renderer.
===============================================================
*/
void Display::draw(Entity *entity)
{
	dstrect[entity->getEntityID()].x = entity->x - camera->x;
	dstrect[entity->getEntityID()].y = entity->y - camera->y;
	dstrect[entity->getEntityID()].w = entity->width;
	dstrect[entity->getEntityID()].h = entity->height;

	if (entity->rotating) {
		SDL_RenderCopyEx(renderer, entityTexture[entity->getEntityID()], NULL, &dstrect[entity->getEntityID()], entity->angle, NULL, SDL_FLIP_NONE); //Rotating sprite
	}
	else if (entity->direction == 0) {
		SDL_RenderCopyEx(renderer, entityTexture[entity->getEntityID()], NULL, &dstrect[entity->getEntityID()], NULL, NULL, SDL_FLIP_HORIZONTAL); //flipped sprite
	}
	else {
		SDL_RenderCopy(renderer, entityTexture[entity->getEntityID()], NULL, &dstrect[entity->getEntityID()]); //draw entity
	}
}

/*
============================Draw()=============================
Draw the lines of the world brushes using rects. They are green.
===============================================================
*/
void Display::draw(World *world)
{
	int camX = camera->x;
	int camY = camera->y;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

	if (world->lines) { //If we want to display the red box for sprite demo.


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
	}
	for (int i = 0; i < world->brushCount; i++) { //Update the rect positions relative to the camera.
		rects[i].x = world->brushes[i]->x - camX;
		rects[i].y = world->brushes[i]->y - camY;
		rects[i].w = world->brushes[i]->w;
		rects[i].h = world->brushes[i]->h;

		//wont work here
		SDL_SetRenderDrawColor(
			renderer,
			world->brushes[i]->color[0],
			world->brushes[i]->color[1],
			world->brushes[i]->color[2],
			world->brushes[i]->color[3]
		);
	}

	//Draw all the rects in the brush array in one call!
	SDL_RenderDrawRects(
		renderer,
		rects,
		world->brushCount
	);
}

//Not used yet.
void Display::draw(Hud *hud)
{
	cout << hud->GetElementString(0) << endl;
}

/*
============================Draw()=============================
Draw our matrix of background textures relative to the camera.
===============================================================
*/
void Display::draw(Background *background)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			dstrect[2].x = background->xCoords[i] - camera->x;
			dstrect[2].y = background->yCoords[j] - camera->y;
			SDL_RenderCopy(renderer, entityTexture[2], NULL, &dstrect[2]); //draw entity
		}
	}
}

/*
============================Draw()=============================
Used for drawing buttons since we have not implemented textured
buttons yet. Just draws a rectangle.
===============================================================
*/
void Display::draw(const int t_x, const int t_y, const int t_w, const int t_h) {
	
	buttonRect.x = t_x;
	buttonRect.y = t_y;
	buttonRect.w = t_w;
	buttonRect.h = t_h;

	/*
	THIS IS THE WORST THING I HAVE EVER DONE.
	*/
	SDL_SetRenderDrawColor(renderer, 0x89, 0x37, 0xA4, 0xFF); 
	if (t_y == 200) {
		SDL_RenderCopy(renderer, entityTexture[4], NULL, &buttonRect); //draw entity
	}
	else if (t_y == 300) {
		SDL_RenderCopy(renderer, entityTexture[5], NULL, &buttonRect); //draw entity
	}
	else if (t_y == 400) {
		SDL_RenderCopy(renderer, entityTexture[6], NULL, &buttonRect); //draw entity
	}
	else {
		SDL_RenderCopy(renderer, entityTexture[7], NULL, &buttonRect); //draw entity
	}
	
	SDL_RenderDrawRect(renderer, &buttonRect);

}

/*
============================GameOver()=============================
Clear the screen with white.
===============================================================
*/
void Display::GameOver()
{
	SDL_UpdateWindowSurface(window);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //background fill 
	SDL_RenderClear(renderer);
	render();
}

/*
============================render()===========================
Render the current frame to the screen. If the console is active,
draw it. Otherwise just present the renderer, which has already
been prepared from render calls above.
===============================================================
*/
void Display::render()
{
	//Test render text
	//SDL_RenderCopy(renderer, fontTexture, NULL, &textRect[0]);

	if (drawConsoleThisFrame) {
		PrintText();
		drawConsoleThisFrame = false;
	}

	//SDL_RenderCopy(renderer, letterTextures[messageLog[0].letterIndex[2]], NULL, messageLog[0].rects);

	SDL_RenderPresent(renderer);	//This updates the screen with what has been drawn on the renderer

}

/*
============================SetCamera()========================
Set the current camera we use for our offset, good when switching
between active scenes.
===============================================================
*/
void Display::SetCamera(Camera *t_camera)
{
	camera = t_camera;
}

/*
============================DrawConsole()======================
If a message needs to be displayed by the console: for each
letter in the message, iterate through the letter array until
we've found a match, then save that index for drawing our
letter textures onto the renderer.
(letters[n] = lettertextures[n])
===============================================================
*/
void Display::DrawConsole()
{
	std::string text = console.SGetMessage();

	int i = 0;
	int pointer = 0;
	const int spacing = 20;
	int messageLength = 0;
	while (text[i] != 0) {
		for (int j = 0; j < 37; j++) {
			if (text[i] == letters[j]) {
				messageLog[0].rects[i] = letterRect[j];
				messageLog[0].rects[i].x = pointer;
				//messageLog[0].rects[i].y = 0;
				messageLog[0].letterIndex[i] = j;
				pointer += letterRect[j].w;
				j = 38; //exit for by going over limit
			}
		}
		i++;
	}

	messageLog[0].messageLength = i;
	drawConsoleThisFrame = true;
}


