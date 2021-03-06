// enemy.cpp
// Alex Rutan
// 1//3/16
#include <iostream>
#include "enemy.h"
#include "entity.h"
#include "basescene.h"

using namespace std;

Enemy::Enemy()
{
    //speed = 10;
    xVelocity = 0;
	yVelocity = 0;
    //end protected inherited vars

	dir[0] = true;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;
	dir[4] = false;

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

Enemy::Enemy(int t_mode, BaseScene *t_scene)
{
	scene = t_scene;
	mode = t_mode;
	//speed = 10;
	xVelocity = 0;

	collided[0] = false;
	collided[1] = false;

	dir[0] = false;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;
	dir[4] = false;

	// if it's 1 or 2, change the direction.
	if (t_mode < 3) {
		dir[t_mode] = true;
	}

	if (t_mode == ROTATE) {
		rotating = true;
	}

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
} //end constructor

Enemy::~Enemy()
{
} //end deconstructor

bool shrinking = false;
void Enemy::update()
{
	if (!dying)
	{
		if (mode == SCALE) {
			if (shrinking) {
				width--;
				height--;
				if (width < 5) {
					shrinking = false;
				}
			}
			else {
				width++;
				height++;
				if (width > 100) {
					shrinking = true;
				}
			}
		}
		else if (mode == ROTATE) {
			angle++;
			if (angle > 359) {
				angle = 0;
			}
		}
		else {
			if (collided[0])kill(); //if collided with player (entID = 0)

			if (!collided[1])
			{
				x = newX;
				y = newY;

				if (x < 0)
				{
					x = 800;
				}

				if (x > 800)
				{
					x = 0;
				}
			}
			else
			{
				dir[0] = true;
				dir[1] = false;
				dir[2] = false;
				xVelocity = 0;
				yVelocity = 0;
				//scene->HandleCommand(&jump);
			}
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

void Enemy::tryMove()
{
    if(right)
    {
//	xNew = x + 5;
    }
    if(left)
    {
//	xNew = x - 5;
    }
//    if(!yCollided)
//    {
//	airbound = true;
//    } //end if
    
} //end move

void Enemy::fall()
{
    if(y < 10000)//max y dist at 800
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

void Enemy::checkBottom()
{
//    if(yCollided)
//        //y = bottom - height;
//	airbound = false;
//	yVelocity = 0;
 //   } //end if
} //end checkBottom

void Enemy::move()
{
 //   if(xCollided == 0)
    {
 //       x = xNew;
    }
  //  else
  //  {
	if(right)
	{
	    right = false;
	    left = true;
	}
	else
	{
	    right = true;
	    left = false;
	}
  //  }
//    if(airbound)
//    {
	//fall();
   // } //end if

}

void Enemy::hit()
{
    cout << "Enemy OW!!" << endl;
}
