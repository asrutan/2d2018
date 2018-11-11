// entity.h
// Alex Rutan
// 1/3/16

#ifndef ENTITY_EXIST
#define ENTITY_EXIST

#include "queue.h"
const int MF_JUMP = 1;
const int MF_FIRE = 32;
const int MF_LEFT = 4;
const int MF_RIGHT = 8;

class Scene;
class Player;

class Entity{

    protected:
		int PRINTTEST = 1;
		int TIMETEST = 2;
		int FIRE = 3;
		int COOLDOWN = 4;

		int mFlags = 0;

		int speed = 1;
		int spriteX;
		int spriteY;
		int newX = 0;
		int newY = 0;
		int xVelocity = 0;
		int yVelocity = 0;
		bool dead = false;
		bool dying = false;
		bool dir[5];
		int entityID; //TYPE OF ENTITY (Player, Enemy, etc.)
		int uniqueID; //IDENTIFIER IN CURRENT SESSION
		int listID; //CURRENT SPOT IN ENTITY LIST
		int friction = 1;
		int acceleration = 1;
		unsigned int *time;

		struct GameAction{
			int action;
		};

		Queue queue;

    public:
        Entity();
		//Entity(Game*);
        //~Entity();
		Entity(unsigned int *time, const int type);
		virtual ~Entity();
        virtual void update();
		int x; // CHANGE THESE VALUES BACK TO PRIVATE
		int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
		int height;
		int width;
		int direction = 0;
		//void mover(int);
		//void move();
		//string sprite;
		void setListID(int id);
		int getListID();
		int getEntityID();
		bool getIsDead();
		void kill();
		void TestQueue();
		bool collided[2];
		bool onGround = false;
		bool wallHit = false;
		bool collideSide[4]; //1=right 2=left 3=top 4=bottom
		void setXY(int, int);
		void setNewXY(int, int);
		int getX();
		int getY();
		int getXVelocity();
		int getYVelocity();
		void setXVelocity(int);
		void setYVelocity(int);
		bool getDir(int);
		int getFriction();
		int getSpeed();
		int getAcceleration();
		virtual void Fire();
		virtual void CooldownOff();
		void DoMethod(int);
		void Move();
		void Input(int t_flags);
		virtual int GameRequest();

		//for rotating demo
		bool rotating = false;
		double angle = 0;

		virtual void SetScene(Scene *t_game);

		Player& NewPlayer();

}; //end Entity

#endif //ENTITY_EXISTS