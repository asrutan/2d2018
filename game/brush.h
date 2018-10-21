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

    public:
        Brush(int t_x, int t_y, int t_w, int t_h, int t_type);
        ~Brush();

		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		int type = 0;
		int color[4];

	void Define();
}; //end brush

#endif //BRUSH_EXISTS
