// bailey_player.cpp
// Bailey Dishman
// 12/5/2018

#include <iostream>
#include <cmath>
#include "bailey_player.h"
#include "game.h"
#include "console.h"

using namespace std;

Scene *BaileyScene = nullptr;
//Or set to nullptr idr.

/*
==========================BaileyPlayer()=============================
Set variables and flags for the BaileyPlayer character.
===============================================================
*/
BaileyPlayer::BaileyPlayer(unsigned int *Time)
{
	spriteX = 50;
	spriteY = 5;
	speed = 15;

	collided[0] = false;
	collided[1] = false;

	x = 0;
	y = 0;
	height = 112;
	width = 78;

	entityID = 0;
	onGround = false;
	this->xVelocity = 4;


	time = Time;
	queue.SetTimePtr(time);
	anim.loadWalkAnim();

} 

BaileyPlayer::BaileyPlayer()
{

}

BaileyPlayer::~BaileyPlayer()
{

} 

/*
==========================update()=============================
Update states and move the BaileyBaileyPlayer based on them.
===============================================================
*/
void BaileyPlayer::update()//changed from entity
{
	if (dying)dead = true; //Kill the BaileyPlayer

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
			yVelocity += 1;
		}
	}
	Move();

	DoMethod(queue.Execute()); 

} //end update

/*
==========================Move()===============================
Evaluate flags that are set in Input()
Experimenting with cool bitwise flags
===============================================================
*/
void BaileyPlayer::Move()
{
	//cout << "move" << endl;
	y += yVelocity;
	//x += xVelocity;
	if (mFlags & MF_LEFT && !collideSide[1]) {
		x -= 5;
		direction = 0;
		//Alert("BaileyPlayer facing left");
		mFlags &= ~(MF_LEFT);
	}
	if (mFlags & MF_RIGHT && !collideSide[0]) {
		//anim.playWalkAnim();
		direction = 1;
		//Alert("BaileyPlayer facing right");
		//Alert("the BaileyPlayer is facing right");
		x += 5;
		mFlags &= ~(MF_RIGHT);
	}

	if (mFlags & MF_FIRE) {
		queue.Push(FIRE, 0, false, 0);
		mFlags &= ~(MF_FIRE);

	}
}

void BaileyPlayer::Input(int t_flags) {
	//mFlags |= t_flags;
}

/*
==========================Fire()===============================
Spawn a bullet (or just an enemy) in the direction we're facing
===============================================================
*/
void BaileyPlayer::Fire() {
	if (!fireCooldown) {
		cout << "BANG" << endl;
		scene->spawn(3);
		fired = true;
		fireCooldown = true;
		queue.Push(4, coolDownTime, false, 0);
	}
}

void BaileyPlayer::CooldownOff() {
	fireCooldown = false;
}

void BaileyPlayer::Jump()
{
		// COMMENT: Commented out this section so that he will only walk back and forth
	/*
	if (onGround) {
		y--;
		yVelocity = -30;
		onGround = false;
	}
	*/
	mFlags &= ~(MF_JUMP); //Set opposite of jump
	//Alert("BaileyPlayer jumped");
}

/*
=========================SetScene()============================
BaileyPlayer receives a pointer to the scene in which he exists so
he can call functions within scene.
===============================================================
*/
void BaileyPlayer::SetScene(BaseScene * t_scene)
{
	scene = t_scene;
	int sixtynine = testExt;
	Alert("BaileyPlayer says hi");
}

/*
=========================GameRequest()============================
Did we fire?
===============================================================
*/
int BaileyPlayer::GameRequest() {
	if (fired) {
		fired = false;
		return 1;
	}
	return 0;
}