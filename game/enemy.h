// enemy.h
// Alex Rutan
// 1/3/16

#ifndef ENEMY_EXIST
#define ENEMY_EXIST

#include "collideBox.h"
#include "entity.h"

class Enemy : public Entity
{
    private:
		int jumpStrength;
		const int RIGHT = 1;
		const int LEFT = 2;
		const int SCALE = 3;
		const int ROTATE = 4;
		int mode = 0;
		//int dir;

    public:
        Enemy();
		//Enemy(int direction);
		Enemy(int t_mode, BaseScene *scene);
        ~Enemy();
        virtual void tryMove();
		virtual void move();
        virtual void update();
		void fall();
		virtual void hit();
		void checkBottom();
		bool left;
		bool right;
		int frame; //animation frame TEST
		int tick; //for animation frame TEST
}; //end Enemy

#endif //ENEMY_EXISTS
