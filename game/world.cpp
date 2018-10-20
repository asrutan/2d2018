// world.cpp
// Alex Rutan
// 11/22/15
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "world.h"
#include "brush.h"

using namespace std;

World::World()
{
}


/*
World::World(Display* d, string fileName)
{
    loadWorld(fileName, d);
}
*/

World::~World()
{
} //end destructor

void World::define()
{
	horizonts[0] = new horizontal;
	horizonts[0]->y = 500;
	horizonts[0]->x1 = 100;
	horizonts[0]->x2 = 600;

	verts[0] = new vertical;
	verts[0]->x = 100;
	verts[0]->y1 = 100;
	verts[0]->y2 = 500;

	verts[1] = new vertical;
	verts[1]->x = 600;
	verts[1]->y1 = 100;
	verts[1]->y2 = 500;

	//Test brush
	Brush *testBrush = new Brush(SOLID,0,0,50,50);
}