// world.h
// Alex Rutan
// 11/22/15

#ifndef WORLD_EXIST
#define WORLD_EXIST

#include <vector>
#include <string>
#include "tile.h"

class World
{
    private:
	//std::vector<Tile> tiles;
	//int stringToInt(std::string);

    public:
        World();
	//World(Display*);
	//World(Display*, std::string);
        ~World();
	//void loadWorld(std::string, Display*);

	struct horizontal {
		int y;
		int x1;
		int x2;
	};

	struct vertical {
		int x;
		int y1;
		int y2;
	};

	vertical * verts[255];
	horizontal * horizonts[255];

	void define();
}; //end World(lol)

#endif //WORLD_EXISTS
