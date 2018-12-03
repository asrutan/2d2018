// background.h
// Alex Rutan
// 1/5/16

#ifndef BACKGROUND_EXIST
#define BACKGROUND_EXIST

class Scene;
class Background
{
	private:
		Scene *scene = nullptr;
		int sWidth = 0;

    public:
        Background();
        ~Background();
		void SetScene(Scene* scene);
		void Update();
		int yCoords[3];
		int xCoords[3];
        int xm = 0;
		int ym = 0;
		int xr = 0;
		int yr = 0;
		int xl = 0;
		int yl = 0;
		int w;
		int h;
		int temp = 0;
		const char* textureFile;
        
}; //end Background

#endif //BACKGROUND_EXISTS
