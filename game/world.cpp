// world.cpp
// Alex Rutan
// 11/22/15
// mod 11/10/18
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "world.h"
#include "brush.h"
#include "console.h"

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

/*
===========================CreateBrush()=======================
Create new world geometry, increment our counter of world
geometries.
===============================================================
*/
void World::CreateBrush(int t_x, int t_y) {
	brushes[brushCount] = new Brush(t_x, t_y, 0, 0, SOLID);
	brushCount++;
}

void World::CreateBrush(int t_x, int t_y, int t_w, int t_h, int t_type) {
	brushes[brushCount] = new Brush(t_x, t_y, t_w, t_h, t_type);
	brushCount++;
}

/*
===========================EditBrush()=========================
When the mouse is held down, this function is called to change
the current width and height of the brush. Set allnormal to
false because after the mouse is released, we have to normalize.
===============================================================
*/
void World::EditBrush(int t_x, int t_y)
{
	//cout << t_x << endl;
	brushes[brushCount - 1]->w = t_x - brushes[brushCount - 1]->x;
	brushes[brushCount - 1]->h = t_y - brushes[brushCount - 1]->y;
	m_allNormal = false;
}

/*
========================NormalizeBrush()=======================
If not every brush is normal, change it so that there are no
negative values in the width or height. If they are negative,
collision doesn't know what to do.
===============================================================
*/
void World::NormalizeBrush() {
	if (!m_allNormal)
	{
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

/*
==========================CheckExist()=========================
Check to see if a file that matches the requested map name
exists in the current directory.
===============================================================
*/
bool World::CheckExist(const char * t_name)
{
	string name = t_name;
	string line;
	ifstream myfile(name += ".map");

	if (myfile.is_open())
	{
		myfile.close();
		return true;
	}
	return false;
}


/*
=============================Load()============================
"Load" a map that is hard-coded. Usually used if all else fails.
===============================================================
*/
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

/*
=============================Load()============================
Take the name of a map and try to load the information from
a file. If that fails, create a new empty map.
===============================================================
*/
void World::Load(std::string name)
{
	const int m_brushesLen = 2;
	struct newBrush {
		int t_x;
		int	t_y;
		int t_w;
		int t_h;
		int t_type;
	};

	string str = name;
	if (!LoadFromFile(str)) {
		CreateNew();
	}
}

/*
==========================CreateNew()==========================
Create a pre-defined map. Used when the editor is started.
===============================================================
*/
void World::CreateNew()
{
	lines = false;
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

/* TODO: ELIMINATE
==========================Define()==========================
Old code that creates red lines for a sprite test.
============================================================
*/
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

/*
========================LoadFromFile()=========================
Try to load a file by the same name as the map requested. If 
we can open it, iterate through every 5 numbers for x,y,width,
height, and type. Create a new brush for each five lines, then
close the file.
===============================================================
*/
bool World::LoadFromFile(string filename)
{
	string line;
	ifstream myfile(filename += ".map");
	
	if (myfile.is_open())
	{
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		int type = 0;

		int i = 0;
		while (getline(myfile, line))
		{
			stringstream s(line);
			if (i == 0) {
				s >> x;
			}
			else if (i == 1) {
				s >> y;
			}

			else if (i == 2) {
				s >> w;
			}
			else if (i == 3){
				s >> h;
			}
			else if (i == 4) {
				s >> type;
			}
			else {
				cout << "LoadFromFile index out of bounds!" << endl;
				break;
			}
			if (++i > 4) {
				i = 0;
				CreateBrush(x, y, w, h, type);
			}
		}
		myfile.close();
		return true;
	}
	cout << "Unable to open file";
	return false;
}

/*
========================SaveToFile()===========================
Open or create a file by the name of the map name requested. 
Write the information for each brush in the current world line
by line. Every five lines indicates a new brush.
===============================================================
*/
void World::SaveToFile(string filename) {
	ofstream myfile;
	myfile.open(filename += ".map");
	
	for(int i = 0; i < brushCount; i++){
		for (int j = 0; j < 5; j++) {
			if (j == 0) {
				myfile << brushes[i]->x;
				myfile << "\n";
			}
			else if (j == 1) {
				myfile << brushes[i]->y;
				myfile << "\n";
			}
			else if (j == 2) {
				myfile << brushes[i]->w;
				myfile << "\n";
			}
			else if (j == 3) {
				myfile << brushes[i]->h;
				myfile << "\n";
			}
			else if (j == 4) {
				myfile << brushes[i]->type;
				myfile << "\n";
			}
		}
	}
	myfile.close();
}