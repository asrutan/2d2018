// background.cpp
// Alex Rutan
// 1/5/16

#include "background.h"
#include "scene.h"

Background::Background()
{
    xm = 0;
    ym = 0;
	w = 990;
	h = 780;
	xr = xr + w;
	xl = xl - h;
} //end constructor

Background::~Background()
{
	scene = nullptr;
} //end destructor

void Background::SetScene(Scene * t_scene)
{
	scene = t_scene;
	sWidth = scene->screenWidth;
}

void Background::Update()
{	
	int camx = scene->GetCamX();
	//cout << camx << endl;
	//cout << xr << endl;
	//cout << xm << endl;
	//cout << xl << endl;
	if (camx + w > xm + w) {
		temp = xr;
		xr = xr + w;
		xl = xm;
		xm = temp;
		cout << "RIGHT SWITCH" << endl;
	}

	else if (camx < xm - w) {
		temp = xl;
		xl = xl - w;
		xr = xm;
		xm = temp;
		cout << "LEFT SWITCH" << endl;
	}

	//if()
}
