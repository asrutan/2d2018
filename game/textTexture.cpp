//PA
//textTexture.cpp
//11/22/15

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <cmath>
#include "texture.h"
#include "display.h"
#include "textTexture.h"

using namespace std;

textTexture::textTexture()
{
    //Not used
    myTexture = NULL;
    textFont = NULL;
    textWidth = 0;
    textHeight = 0;
}

textTexture::textTexture(Display* d)
{
    display = d;

    myTexture = NULL;
    textFont = NULL;
    textWidth = 0;
    textHeight = 0;
}

textTexture::~textTexture()
{
    releaseTextTexture();
}

bool textTexture::loadFontMedia(string path)
{
    //finds font file and loads it. then will write using the call to loadFontFromRenderedText

    //Loading success flag
    bool success = true;
    //cout << "About to load font" << endl;
    //Open the font
    textFont = TTF_OpenFont(path.c_str(), 28);
    if(textFont == NULL)
    {
        cout << "Failed to load font! SDL_ttf Error: " << '\n' <<  TTF_GetError() << endl;
       	success = false;
    }
    else
    {
        //cout << "Font Loaded" << endl;
       	//Render text
       	SDL_Color textColor = { 225, 225, 225 };
       	if(!loadFontFromRenderedText("Madoka 4 lyfe!!", textColor))
	{
  	    cout << "Failed to render text texture!\n" << endl;
       	    success = false;
       	}
    }

    return success;
}//end loadFontMedia

bool textTexture::loadFontFromRenderedText(string textAsTexture, SDL_Color textColor)
{
    //gets Font and writes messgae in font to a Surface. Then makes a Texture from that Surface

    //Get rid of existing texture
    releaseTextTexture();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, textAsTexture.c_str(), textColor);
    if(textSurface == NULL)
    {
        //cout << "Surface not Made" << endl;
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    else
    {
        //cout << "Surface made" << endl;
        //Create texture from surface pixels
        myTexture = SDL_CreateTextureFromSurface(display->getRenderer(), textSurface);
        if(myTexture == NULL)
        {
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
        }
        else
        {
	    //cout << "Texture made" << endl;
   	    //Get image dimensions
       	    textWidth = textSurface->w;
	    textHeight = textSurface->h;
	    //cout << textWidth << endl;
	    //cout << textHeight << endl;
	}

       	//Get rid of old surface
       	SDL_FreeSurface(textSurface);
	}
	
    //Return success
    return myTexture != NULL;
}//end loadFontFromRenderedText

void textTexture::releaseTextTexture()
{
    //Free texture if it exists
  if(myTexture != NULL)
    {
        SDL_DestroyTexture(myTexture);
       	myTexture = NULL;
       	textWidth = 0;
       	textHeight = 0;
    }
}//end releaseTextTexture

void textTexture::renderTextTexture(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //places texture on "canvas" (renderer). still needs call "paint" (SDL_RenderPresent)
  
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    //Set clip rendering dimensions
    if(clip != NULL)
    {
      	renderQuad.w = clip->w;
       	renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(display->getRenderer(), myTexture, clip, &renderQuad, angle, center, flip);
    //SDL_RenderCopy(renderer, textTexture, NULL, NULL);
}//end renderTextTexture

int textTexture::getFontFileWidth()
{
    //returns width of text texture
    return textWidth;
}//end getFontWidth

int textTexture::getFontFileHeight()
{
    //returns height of text texture
    return textHeight;
}//end getFontHeight
