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

	for (int i = 0; i < 3; i++) {
		yCoords[i] = h * i;
		xCoords[i] = w * i;
	}

} //end constructor

Background::~Background()
{
	scene = nullptr;
} //end destructor

void Background::SetScene(BaseScene * t_scene)
{
	scene = t_scene;
	sWidth = scene->screenWidth;
}

/*
void Background::SetScene(Scene * t_scene)
{
	scene = t_scene;
	sWidth = scene->screenWidth;
}
*/

void Background::Update()
{	
	int camx = scene->GetCamX();
	int camy = scene->GetCamY();
	//cout << camx << endl;
	//cout << xr << endl;
	//cout << xm << endl;
	//cout << xl << endl;
	if (camx + w > xCoords[1] + w) {
		temp = xCoords[2];
		xCoords[2] = xCoords[2] + w;
		xCoords[0] = xCoords[1];
		xCoords[1] = temp;
		//cout << "RIGHT SWITCH" << endl;
	}

	else if (camx < xCoords[1] - w) {
		temp = xCoords[0];
		xCoords[0] = xCoords[0] - w;
		xCoords[2] = xCoords[1];
		xCoords[1] = temp;
		//cout << "LEFT SWITCH" << endl;
	}

	if (camy + h > yCoords[1] + h) {
		temp = yCoords[2];
		yCoords[2] = yCoords[2] + h;
		yCoords[0] = yCoords[1];
		yCoords[1] = temp;
		//cout << "DOWN SWITCH" << endl;
	}

	else if (camy < yCoords[1] - h) {
		temp = yCoords[0];
		yCoords[0] = yCoords[0] - h;
		yCoords[2] = yCoords[1];
		yCoords[1] = temp;
		//cout << "UP SWITCH" << endl;
	}

	//if()
}
