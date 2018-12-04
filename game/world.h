// world.h
// Alex Rutan
// 11/22/15

#ifndef WORLD_EXIST
#define WORLD_EXIST

#include <vector>
#include <string>
#include "tile.h"
#include "brush.h"

class World
{
    private:
	//std::vector<Tile> tiles;
	//int stringToInt(std::string);
		bool m_allNormal = true;

    public:
        World();
	//World(Display*);
	//World(Display*, std::string);
        ~World();
	//void loadWorld(std::string, Display*);

		void Load();
		void Load(std::string name);
		void CreateBrush(int t_x, int t_y);
		void CreateBrush(int t_x, int t_y, int t_w, int t_h, int t_type);
		void EditBrush(int t_x, int t_y);
		void NormalizeBrush();
		bool CheckExist(const char* name);

		bool LoadFromFile(std::string filename);
		void SaveToFile();

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

		vertical *verts[255];
		horizontal *horizonts[255];

		int brushCount = 0;
		Brush *brushes[255];

		void define();
}; //end World(lol)

#endif //WORLD_EXISTS
