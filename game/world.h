// world.h
// Alex Rutan
// 11/22/15

#ifndef WORLD_EXIST
#define WORLD_EXIST

#include <string>
#include "tile.h"
#include "brush.h"

class World
{
    private:

		bool m_allNormal = true;

    public:
        World();
        ~World();

		void Load();
		void Load(std::string name);
		void CreateNew();
		void CreateBrush(int t_x, int t_y);
		void CreateBrush(int t_x, int t_y, int t_w, int t_h, int t_type);
		void EditBrush(int t_x, int t_y);
		void NormalizeBrush();
		bool CheckExist(const char* name);

		bool LoadFromFile(std::string filename);
		void SaveToFile(std::string filename);

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

		bool lines = true; //Whether or not to draw the red lines indicating the sprite test.
}; //end World

#endif //WORLD_EXISTS
