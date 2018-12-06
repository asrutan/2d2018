// bailey_player.h
// Bailey Dishman
// 12/5/2018

#ifndef BAILEY_PLAYER_EXIST
#define BAILEY_PLAYER_EXIST

#include "collideBox.h"
#include "entity.h"
#include "animation.h"
#include "bailey_enemy.h"

class BaileyPlayer : public Entity
{
	private:

		collideBox aBox;
		Animation anim;
		char lastMove;

		const int IF_LEFTMOUSE = 2;
		const int IF_LEFT = 4;
		const int IF_RIGHT = 8;

		bool fireCooldown = false;
		const int coolDownTime = 200;

		bool fired = false;

	public:

		BaileyPlayer();
		BaileyPlayer(unsigned int *time);
		~BaileyPlayer();
		void update();
		bool quit;
		void Move();
		void Input(int);
		void Fire();
		int GameRequest();
		void CooldownOff();

		void Jump();

		void SetScene(BaseScene * scene);

}; //end Player

#endif //PLAYER_EXISTS