// player.cpp
// Alex Rutan
// 11//21/15
#include <iostream>
#include <cmath>
#include "player.h"
#include "game.h"
#include "console.h"

using namespace std;

Scene *scene = nullptr;
//Or set to nullptr idr.

/*
==========================Player()=============================
Set variables and flags for the player character.
===============================================================
*/
Player::Player(unsigned int *Time)
{
    spriteX = 50;//wraps collision box closer to sprite
    spriteY = 0;
    speed = 15;//movement speed
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

	//Game *game;
} //end constructor

Player::Player()
{

} //end constructor

Player::~Player()
{
} //end deconstructor

//void Player::Init(Game game)
//{
//}

/*
==========================update()=============================
Update states and move the player based on them.
===============================================================
*/
void Player::update()//changed from entity
{
	if (dying)dead = true; //Kill the player

	/*
	if (console.GetMessage() == "jump") {
		Jump();
	}
	*/
	/*
	Do commands in cbus, can only jump.
	*/
	Command *command = scene->cbus.DoCommand();
	if (command != NULL) {
		command->Execute(this);
	}
	command = nullptr;

	if (!onGround) //fall
	{	
		if (yVelocity < 10) {
			//cout << yVelocity << endl;
			yVelocity += 1;
		}
	}
	Move();
	//printf("Player x: %d ", x);
	//TestQueue();
	DoMethod(queue.Execute()); //Queue methods
} //end update

/*
==========================Move()===============================
Evaluate flags that are set in Input()
Experimenting with cool bitwise flags
===============================================================
*/
void Player::Move()
{
	//cout << "move" << endl;
	y += yVelocity;
	//x += xVelocity;
	if (mFlags & MF_LEFT) {
		x -= 5;
		direction = 0;
		//Alert("player facing left");
		mFlags &= ~(MF_LEFT);
	}
	if (mFlags & MF_RIGHT) {
		direction = 1;
		//Alert("player facing right");
		//Alert("the player is facing right");
		x += 5;
		mFlags &= ~(MF_RIGHT);
	}
	if (mFlags & MF_JUMP) {
		Jump();
	}

	if (mFlags & MF_FIRE) {
		queue.Push(FIRE, 0, false, 0);
		mFlags &= ~(MF_FIRE);

	}
}

void Player::Input(int t_flags) {
	//mFlags |= t_flags;
}

/*
==========================Fire()===============================
Spawn a bullet (or just an enemy) in the direction we're facing
===============================================================
*/
void Player::Fire() {
	if (!fireCooldown) {
		cout << "BANG" << endl;
		scene->spawn(3);
		fired = true;
		fireCooldown = true;
		queue.Push(4, coolDownTime, false, 0);
	}
}

void Player::CooldownOff() {
	fireCooldown = false;
}

void Player::Jump()
{
	if (onGround) {
		y--;
		yVelocity = -30;
		onGround = false;
	}
	mFlags &= ~(MF_JUMP); //Set opposite of jump
	//Alert("player jumped");
}

/*
=========================SetScene()============================
Player receives a pointer to the scene in which he exists so
he can call functions within scene.
===============================================================
*/
void Player::SetScene(BaseScene * t_scene)
{
	scene = t_scene;
	//cout << "SETSCENE" << endl;
	int sixtynine = testExt;
	//cout << sixtynine << endl;
	Alert("player says hi");
}

/*
=========================GameRequest()============================
Did we fire?
===============================================================
*/
int Player::GameRequest() {
	if (fired) {
		fired = false;
		return 1;
	}
	return 0;
}