// camera.h
// Alex Rutan
// 12/1/15

// Edited: 10/20/18

#ifndef CAMERA_EXIST
#define CAMERA_EXIST

#include "entity.h"
#include "enemy.h"
#include "world.h"

class Camera
{
    private:
        Entity *parent = nullptr;
        int xTarget;
		int yTarget;
		int xVelocity;
		int yVelocity;
		bool campan = true;
		bool free = true;

    public:
        Camera();
		Camera(Entity*);
		~Camera();
		void Init(Entity*);
		void update();
		void move();
        int x;
		int y;
	//bool init();
	//	bool loadTextures();
};

#endif

