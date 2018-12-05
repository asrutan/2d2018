// sound.h
// Bailey Dishman
// 12/3/2018

#ifndef SOUND_EXIST
#define SOUND_EXIST

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <iostream>


// Sound


class Sound
{

	public:

		// Background music
		Mix_Music *bgMusic = NULL;

		// The sound effects that will be used
		Mix_Chunk *soundEffect = NULL;

		// Default Constructor
		Sound();

		// Destructor
		~Sound();

		// Play background music
		bool playBGMusic();
		void pauseBGMusic();
		void resumeBGMusic();
		void stopBGMusic();

	private:

		// Initialize SDL mixer
		bool mixerInit();


};

#endif