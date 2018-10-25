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

		bool fireCooldown = false;
		int coolDownTime = 1000;

		//test firing in game
		bool fired = false;

    public:
        Player();
		Player(unsigned int *time);
		~Player();
		//void Init();
        void update();
		bool quit;
		void Move();
		void Input(int);
		void Fire();
		int GameRequest();
		void CooldownOff();

		void SetGame(Game * t_game);

		//template<typename T>
		//void SetGame(T *t_game);

}; //end Player

#endif //PLAYER_EXISTS