// brush.cpp
// Alex Rutan
// 10/19/18
#include <iostream>
#include "brush.h"

using namespace std;

Brush::Brush(int Type, int X1, int Y1, int X2, int Y2){
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
	type = Type;

	printf("New Brush Spawned At: (%d,%d) (%d,%d)\n", x1, y1, x2, y2);
}

Brush::~Brush(){
} //end destructor

void Brush::Define(){
	

}