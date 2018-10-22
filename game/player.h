// player.h
// Alex Rutan
// 11/21/15

#ifndef PLAYER_EXIST
#define PLAYER_EXIST

#include "collideBox.h"
#include "entity.h"

class Player : public Entity
{
    private:
		collideBox aBox;
		char lastMove;

		const int IF_SPACE = 1;
		const int IF_LEFTMOUSE = 2;
		const int IF_LEFT = 4;
		const int IF_RIGHT = 8;

    public:
        Player();
		Player(unsigned int *time);
		~Player();
        void update();
		bool quit;
		void Move();
		void Input(int);

}; //end Player

#endif //PLAYER_EXISTS
