// enemy.cpp
// Alex Rutan
// 1//3/16
#include <iostream>
#include "bailey_enemy.h"
#include "entity.h"
#include "basescene.h"

using namespace std;

BaileyEnemy::BaileyEnemy()
{
	//speed = 10;
	xVelocity = 0;
	yVelocity = 0;
	//end protected inherited vars

	newX = 0;
	newY = 0;

	x = 0;
	y = 0;

	//end public inherited vars
	left = false;
	right = true;
	tick = 0;
	frame = 0;
	//end new vars

	entityID = 1;
} //end constructor

BaileyEnemy::BaileyEnemy(int t_mode, BaseScene *t_scene)
{
	scene = t_scene;
	mode = t_mode;
	//speed = 10;
	xVelocity = 0;

	collided[0] = false;
	collided[1] = false;

	if (t_mode == 1)
	{

		dir[4] = true;

	}

	// if it's 1 or 2, change the direction.
	//if (t_mode < 3) {
		//dir[t_mode] = true;
	//}

	//if (t_mode == ROTATE) {
	//	rotating = true;
	//}

	speed = 10;
	acceleration = 1;
	xVelocity = 0;
	yVelocity = 0;
	//end protected inherited vars

	newX = 0;
	newY = 0;

	x = 0;
	y = 0;

	//end public inherited vars
	left = false;
	right = true;
	tick = 0;
	frame = 0;
	//end new vars

	entityID = 1;

	rotating = true;
} //end constructor

BaileyEnemy::~BaileyEnemy()
{
} //end deconstructor

void BaileyEnemy::update()
{

	if (!dying)
	{
		if (collided[0]) {
			scene->score++;
			kill();
		}//if collided with player (entID = 0)

		if (onGround)kill();

		if (!collided[1])
		{
			move();
		}

		angle += speed;
		if (angle > 360) {
			angle = 0;
		}
	}
	else
	{
		if (height > 0 && width > 0)
		{
			height -= 2;
			width -= 2;
		}
		else dead = true;
	}

} //end update

void BaileyEnemy::tryMove()
{
	if (right)
	{
		//	xNew = x + 5;
	}
	if (left)
	{
		//	xNew = x - 5;
	}
	//    if(!yCollided)
	//    {
	//	airbound = true;
	//    } //end if

} //end move

void BaileyEnemy::fall()
{
	if (y < 10000)//max y dist at 800
	{
		//      y = y - yVelocity;
			 // yVelocity--;
		  //if(yVelocity <= -45)
		  //{
		  //    yVelocity = -45;
		  //}
		checkBottom();
	}
	else
	{
		y = 799;
		//yVelocity = 0;
	//	airbound = false;
	//	yCollided = true;
	}
} //end fall

void BaileyEnemy::checkBottom()
{
	//    if(yCollided)
	//        //y = bottom - height;
	//	airbound = false;
	//	yVelocity = 0;
	 //   } //end if
} //end checkBottom

void BaileyEnemy::move()
{

	if (yVelocity < speed)
	{
		yVelocity += acceleration;
	}
	y += yVelocity;
}

void BaileyEnemy::hit()
{
	cout << "Enemy OW!!" << endl;
}
