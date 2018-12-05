// sound.h
// Bailey Dishman
// 12/3/2018

#include "sound.h"


// Constructors


// Default Constructor
Sound::Sound()
{

	// Initialize SDL mixer
	mixerInit();

	// Load background music
	bgMusic = Mix_LoadMUS("bgMusic.wav");

}


// End of Constructors


// Destructor
Sound::~Sound()
{

	// Free background music
	Mix_FreeMusic(bgMusic);

	// Quit SDL_mixer
	Mix_CloseAudio();

}


// Class Methods


// playBGMusic()
// Play background music
bool Sound::playBGMusic()
{

	// Play background music
	if (Mix_PlayMusic(bgMusic, -1) == -1)
	{
		return false;
	}
	return true;
}

// pauseBGMusic()
// Pause background music
void Sound::pauseBGMusic()
{

	//Pause the music
	Mix_PauseMusic();

}


// resumeBGMusic()
// Resume background music
void Sound::resumeBGMusic()
{

	// If the background music is paused
	if (Mix_PausedMusic() == 1)
	{
		// Resume background music
		Mix_ResumeMusic();
	}

}


// stopBGMusic()
// Stop background music
void Sound::stopBGMusic()
{

	// Stop background music
	Mix_HaltMusic();

}


// End of Class Methods


// Private Methods


// mixerInit()
// Initialize SDL mixer
bool Sound::mixerInit()
{

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}
	return true;
}


// End of Private Methods
