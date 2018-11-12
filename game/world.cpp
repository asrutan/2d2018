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

void World::CreateBrush(int t_x, int t_y) {
	brushes[brushCount] = new Brush(t_x, t_y, 0, 0, SOLID);
	brushCount++;
}

void World::CreateBrush(int t_x, int t_y, int t_w, int t_h, int t_type) {
	brushes[brushCount] = new Brush(t_x, t_y, t_w, t_h, t_type);
	brushCount++;
}

void World::EditBrush(int t_x, int t_y)
{
	//cout << t_x << endl;
	brushes[brushCount - 1]->w = t_x - brushes[brushCount - 1]->x;
	brushes[brushCount - 1]->h = t_y - brushes[brushCount - 1]->y;
	m_allNormal = false;
}

void World::NormalizeBrush() {
	if (!m_allNormal)
	{
		//cout << "NORMALIZE" << endl;
		if (brushes[brushCount - 1]->w < 0) {
			brushes[brushCount - 1]->x += brushes[brushCount - 1]->w;
			brushes[brushCount - 1]->w *= -1;
		}
		if (brushes[brushCount - 1]->h < 0) {
			brushes[brushCount - 1]->y += brushes[brushCount - 1]->h;
			brushes[brushCount - 1]->h *= -1;
		}
	}
	m_allNormal = true;
}

//Hard coded world for now. 
//Load map from file later.
void World::Load() {
	const int m_brushesLen = 2;
	struct newBrush {
		int t_x;
		int	t_y;
		int t_w; 
		int t_h;
		int t_type;
	};

	newBrush newBrushes[m_brushesLen];
	newBrushes[0].t_x = 10; newBrushes[0].t_y = 450; newBrushes[0].t_w = 400; newBrushes[0].t_h = 10; newBrushes[0].t_type = SOLID;
	newBrushes[1].t_x = 400; newBrushes[1].t_y = 550; newBrushes[1].t_w = 400; newBrushes[1].t_h = 50; newBrushes[1].t_type = SOLID;

	for (int i = 0; i < m_brushesLen; i++) {
		CreateBrush(newBrushes[i].t_x, newBrushes[i].t_y, newBrushes[i].t_w, newBrushes[i].t_h, newBrushes[i].t_type);
	}
}

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
	//brushes[0] = new Brush(200,400,75,75,SOLID);
	//brushCount++;
}