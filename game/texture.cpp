// texture.cpp
// Alex Rutan / PA
// 11/22/15
// Bailey Dishman
// 12/4/2018

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <cmath>
#include "display.h"
#include "texture.h"

using namespace std;

//The window renderer
SDL_Renderer* g_Renderer = NULL;


// Constructors


// Default Constructor
Texture::Texture()
{
 
	// Initialize
	m_Width = 0;
	m_Height = 0;

}


// End of Constructors


// Destructor
Texture::~Texture()
{

	clearTexture();

}


// Class Methods


// getWidth()
// Returns the width of the image
int Texture::getWidth()
{
	return m_Width;
}

// getHeight()
// Returns the height of the image
int Texture::getHeight()
{
	return m_Height;
}

// clearTexture()
// Clears any existing texture data
void Texture::clearTexture()
{

	// If a texture already exists, clear the texture
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}

}


// loadTextureFile()
// Loads texture given a file name as a string
bool Texture::loadTextureFile(const char *fileName)
{
	
	// Get rid of any pre-existing texture data
	clearTexture();

    bool success = true;

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image 
	SDL_Surface* loadedSurface = IMG_Load(fileName);

    if(loadedSurface == NULL)
    {

		printf("Unable to load image %s! SDL_image Error: %s\n", fileName, IMG_GetError());

		success = false;

    }
    else
    {

		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(g_Renderer, loadedSurface);

		if(newTexture == NULL)
		{

			printf("Unable to create texture from %s! SDL Error: %s\n", fileName, SDL_GetError());
			success = false;

		}
		else
		{

			// Get image dimensions
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;

		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

    } 

	// Return success
	m_Texture = newTexture;
	return m_Texture != NULL;

} // End of loadTexture()

// render()
// Renders texture at given point
void Texture::render(int x, int y, SDL_Rect * clip)
{

	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopy(g_Renderer, m_Texture, clip, &renderQuad);

}


// End of Class Methods
