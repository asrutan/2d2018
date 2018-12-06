// animation.h
// Bailey Dishman
// 12/4/18

#ifndef ANIMATION_EXIST
#define ANIMATION_EXIST

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "texture.h"

// Animation

class Animation
{

	private:

	public:

		int frame = 0;
		Texture g_SpriteSheetTexture;
		SDL_Rect g_SpriteClips[4];

		// Constructor
		Animation();

		// Destructor
		~Animation();

		// Load walk animation
		bool loadWalkAnim();
		
		// Play walk animation
		void playWalkAnim();

};

#endif