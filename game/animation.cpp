// animation.cpp
// Bailey Dishman
// 12/4/2018

#include "animation.h"


// Constructors


// Default Constructor
Animation::Animation()
{

}


// End of Constructors


// Destructor
Animation::~Animation()
{

	g_SpriteSheetTexture.clearTexture();

}


// Class Methods


// loadWalkAnim()
// Loads walk animation
bool Animation::loadWalkAnim()
{

	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!g_SpriteSheetTexture.loadTextureFile("redDudeWalkAnim.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{

		//Set sprite clips
		g_SpriteClips[0].x = 12;
		g_SpriteClips[0].y = 12;
		g_SpriteClips[0].w = 127;
		g_SpriteClips[0].h = 162;

		g_SpriteClips[1].x = 162;
		g_SpriteClips[1].y = 12;
		g_SpriteClips[1].w = 127;
		g_SpriteClips[1].h = 162;

		g_SpriteClips[2].x = 312;
		g_SpriteClips[2].y = 12;
		g_SpriteClips[2].w = 126;
		g_SpriteClips[2].h = 162;

		g_SpriteClips[3].x = 462;
		g_SpriteClips[3].y = 12;
		g_SpriteClips[3].w = 127;
		g_SpriteClips[3].h = 162;

	}

	return success;

} // End of loadWalkAnim

// playWalkAnim()
// Plays walk animation
void Animation::playWalkAnim()
{

	++frame;

	// Cycle animation
	if (frame >= 4)
	{
		frame = 0;
	}

}


// End of Class Methods
