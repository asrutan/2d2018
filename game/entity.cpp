// entity.cpp
// PA
// 1/5/16
#include <iostream>
#include <cmath>
#include "entity.h"

using namespace std;

//Queue testing
int repeatedTimes = 0;
Entity::Entity()
{
    spriteX = 0;
    spriteY = 0;
    //end private vars
    //x = 200;
   // y = 300;
    height = 50;
    width = 50;
	dir[0] = true;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;
	dir[4] = false;
    //end public var
	//queue.SetEntity(*this);

} //end constructor

/*
Entity::Entity(Game *game)
{
	spriteX = 0;
	spriteY = 0;
	//end private vars
	//x = 200;
	// y = 300;
	height = 50;
	width = 50;
	dir[0] = true;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;
	dir[4] = false;
	//end public var
	//queue.SetEntity(*this);

	cout << "GAME" << endl;
	cout << game->GetTime() << endl;

} //end constructor
*/

Entity::~Entity()
{
} //end deconstructor

void Entity::setListID(int id)
{
	listID = id;
}
int Entity::getListID()
{
	return listID;
}
int Entity::getEntityID()
{
	return entityID;
}
//end setListID

void Entity::update()
{
	//TestQueue();
} //end update

bool Entity::getIsDead()
{
	return dead;
}//end setXY

void Entity::setXY(int mx, int my)
{
	x = mx;
	y = my;
}

void Entity::setNewXY(int mx, int my)
{
	newX = x + mx;
	newY = y + my;
}
int Entity::getX()
{
	return x;
}
int Entity::getY()
{
	return y;
}
int Entity::getXVelocity()
{
	return xVelocity;
}
int Entity::getYVelocity()
{
	return yVelocity;
}
void Entity::setXVelocity(int xVel)
{
	xVelocity += xVel;
}
void Entity::setYVelocity(int yVel)
{
	yVelocity += yVel;
}
bool Entity::getDir(int i)
{
	return dir[i];
}
int Entity::getFriction()
{
	return friction;
}
int Entity::getSpeed()
{
	return speed;
}
int Entity::getAcceleration()
{
	return acceleration;
}
void Entity::DoMethod(int methodId)
{
	if (methodId == PRINTTEST) {
		repeatedTimes++;
		printf("Queue Test %d\n", repeatedTimes);
		if (repeatedTimes == 5) {
			queue.Push(TIMETEST, 0, false, 0);
		}
	}
	if (methodId == TIMETEST) {
		printf("Current time: %d\n", *time);
	}
}
void Entity::Move()
{
}
void Entity::Input(int t_flags)
{
	mFlags |= t_flags;
}
//end setXY


void Entity::kill()
{
	dying = true;
}

void Entity::TestQueue() {
	queue.Push(PRINTTEST, 1000, true, 10);
	queue.Push(TIMETEST, 0, false, 0);
}
