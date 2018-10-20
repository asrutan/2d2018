// camera.h
// Alex Rutan
// 12/1/15

#ifndef CAMERA_EXIST
#define CAMERA_EXIST

#include "player.h"
#include "enemy.h"
#include "world.h"

class Camera
{
    private:
        Player* player;
	Enemy* enemy;
        World* world;
        int xTarget;
	int yTarget;
	int xVelocity;
	int yVelocity;
	bool campan;

    public:
        Camera();
	Camera(Player*, Enemy*, World*);
	~Camera();
	void update();
	void move();
        int x;
	int y;
	//bool init();
	//	bool loadTextures();
};

#endif

