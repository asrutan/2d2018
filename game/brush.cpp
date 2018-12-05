// brush.cpp
// Alex Rutan
// 10/19/18
#include <iostream>
#include "brush.h"

using namespace std;

/*
=============================Brush()===========================
Create a new brush and set its color information and
coordinates. Eventually, brushes of different types will be 
created. For now, they are all solid.
===============================================================
*/
Brush::Brush(int t_x, int t_y, int t_w, int t_h, int t_type){
	x = t_x;
	y = t_y;
	w = t_w;
	h = t_h;

	type = t_type;

	color[0] = 0x00; color[1] = 0xFF; color[2] = 0x00; color[3] = 0x00;

	printf("New Brush Spawned At: (%d,%d) height: %d, width: %d)\n", x, y, h, w);
}

Brush::~Brush(){
} //end destructor

void Brush::Define(){
	

}