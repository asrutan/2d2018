// background.cpp
// Alex Rutan
// 1/5/16

#include "background.h"
#include "basescene.h"

Background::Background()
{
    xm = 0;
    ym = 0;
	w = 990;
	h = 780;
	xr = xr + w;
	xl = xl - h;

	//Create our coordinates for the matrix of background textures
	//This information is used by display.
	for (int i = 0; i < 3; i++) {
		yCoords[i] = h * i;
		xCoords[i] = w * i;
	}

} //end constructor

Background::~Background()
{
	scene = nullptr;
} //end destructor

/*
=============================SetScene()========================
Set this scene pointer to the value of the current scene.
===============================================================
*/
void Background::SetScene(BaseScene * t_scene)
{
	scene = t_scene;
	sWidth = scene->screenWidth; //Width is the current width of the screen defined in display.
}

/*TODO: Should move the scrolling functionality to its own function.
=============================Update()==========================
If the mapname isn't empty, load the map into the scene. Set to
empty name so it doesn't get carried over for the next call to
this command.
===============================================================
*/
void Background::Update()
{	
	//Get camera position.
	int camx = scene->GetCamX();
	int camy = scene->GetCamY();

	/*
	If the screen is off any four of the sides of the screen,
	Shift the three backgrounds per axis over so that the current
	spot in which the player resides is the middle of array (4)
	We do this on the x and y axis.
	*/
	if (camx + w > xCoords[1] + w) { //If the right side of the camera is larger than the right middle side, 
		temp = xCoords[2];
		xCoords[2] = xCoords[2] + w; //Shift the far right texture one width's length to the right
		xCoords[0] = xCoords[1]; //Make the left one take the old center.
		xCoords[1] = temp; //Move the old center to the old right, making it the new center.
	}

	else if (camx < xCoords[1] - w) {
		temp = xCoords[0];
		xCoords[0] = xCoords[0] - w;
		xCoords[2] = xCoords[1];
		xCoords[1] = temp;
	}

	if (camy + h > yCoords[1] + h) {
		temp = yCoords[2];
		yCoords[2] = yCoords[2] + h;
		yCoords[0] = yCoords[1];
		yCoords[1] = temp;
	}

	else if (camy < yCoords[1] - h) {
		temp = yCoords[0];
		yCoords[0] = yCoords[0] - h;
		yCoords[2] = yCoords[1];
		yCoords[1] = temp;
	}
}
