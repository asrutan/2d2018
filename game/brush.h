// brush.h
// Alex Rutan
// 10/19/18

#ifndef BRUSH_EXIST
#define BRUSH_EXIST

#include <vector>
#include <string>

const int SOLID = 0; const int TRIGGER = 1;

class Brush
{
    private:
	//std::vector<Tile> tiles;
	//int stringToInt(std::string);
		int x1;
		int x2;
		int y1;
		int y2;
		int type;

    public:
        Brush(int, int, int, int, int);
        ~Brush();

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

	void Define();
}; //end brush

#endif //BRUSH_EXISTS
