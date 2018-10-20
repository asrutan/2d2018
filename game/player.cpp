// player.cpp
// Alex Rutan
// 11//21/15
#include <iostream>
#include <cmath>
#include "player.h"

using namespace std;

Player::Player(unsigned int *Time)
{
    spriteX = 50;//wraps collision box closer to sprite
    spriteY = 0;
    speed = 10;//movement speed
    //end protected inherited vars

	collided[0] = false;
	collided[1] = false;
	
	x = 400;
    y = 300;
    height = 128;//height of player/sprite - used by collidebox
    width = 95;//width of player/sprite - used by collidebox
    //end public inherited vars

	entityID = 0;
	//sprite = "player.bmp";
	floorHit = false;
	this->xVelocity = 4;
    //make this an array or list or some shit
    //end new vars

	time = Time;
	queue.SetTimePtr(time);
	//Queue testing
} //end constructor

Player::Player()
{

} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()//changed from entity
{
	if (dying)dead = true;

	if (floorHit == false)
	{
		//cout << floorHit << endl;
		y++;
	}

	//TestQueue();
	DoMethod(queue.Execute());
} //end update

void Player::move()
{
	x = x + xVelocity;//update x by xVelocity
}


//void Entity::move()
//{
//	x = x + xVelocity;//update x by xVelocity
//}