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
	onGround = false;
	this->xVelocity = 4;
	//this->yVelocity = 2;
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

	if (!onGround)
	{	
		if (yVelocity < 10) {
			//cout << yVelocity << endl;
			yVelocity += 1;
		}
	}
	Move();
	//printf("Player x: %d ", x);
	//TestQueue();
	DoMethod(queue.Execute());
} //end update

void Player::Move()
{
	//cout << "move" << endl;
	y += yVelocity;
	//x += xVelocity;
	if (mFlags & MF_LEFT) {
		x -= 5;
		mFlags &= ~(MF_LEFT);
	}
	if (mFlags & MF_RIGHT) {
		x += 5;
		mFlags &= ~(MF_RIGHT);
	}
	if (mFlags & MF_JUMP) {
		if (onGround) {
			y--;
			yVelocity = -30;
			onGround = false;		
		}
		mFlags &= ~(MF_JUMP);
	}

	if (mFlags & MF_FIRE) {
		queue.Push(FIRE, 0, false, 0);
		mFlags &= ~(MF_FIRE);

	}
}

void Player::Input(int t_flags) {
	//mFlags |= t_flags;
}

void Player::Fire() {
	if (!fireCooldown) {
		fireCooldown = true;
		queue.Push(4, coolDownTime, false, 0);
	}
}

void Player::CooldownOff() {
	fireCooldown = false;
}

//void Entity::move()
//{
//	x = x + xVelocity;//update x by xVelocity
//}