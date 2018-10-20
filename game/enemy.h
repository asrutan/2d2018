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
		//int dir;

    public:
        Enemy();
		Enemy(int direction);
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
