// animation.h
// Bailey Dishman
// 12/4/18

#ifndef ANIMATION_EXIST
#define ANIMATION_EXIST

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

// Animation

class Animation
{

	private:


	public:

		// Constructor
		Animation();

		// Destructor
		~Animation();

		// Load walk animation
		bool loadWalkAnim();
		
		void playWalkAnim();

};

#endif