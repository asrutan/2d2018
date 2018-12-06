// movement.cpp
// Alex Rutan
// 11/21/15
#include <iostream>
#include "movement.h"

using namespace std;

/*
==========================Movement()===========================
Exepriment in having a seperate object move entities.
===============================================================
*/


Movement::Movement()
{
} //end constructor

Movement::~Movement()
{
} //end destructor

void Movement::move(Entity *entity)
{
	//0 = stopped
	//1 = right
	//2 = left
	//3 = up
	//4 = down
	if (entity->getDir(0))
	{
		if (entity->getXVelocity() != 0)
		{
			if (entity->getXVelocity() > 0) entity->setXVelocity(entity->getFriction()*-1); //increment by friction

			else if (entity->getXVelocity() < 0) entity->setXVelocity(entity->getFriction());
		}
		if (entity->getYVelocity() != 0)
		{
			if (entity->getYVelocity() > 0) entity->setYVelocity(entity->getFriction()*-1); //increment by friction

			else if (entity->getYVelocity() < 0) entity->setYVelocity(entity->getFriction());
		}
	}
	else
	{
		if (entity->getDir(1)) // move right
		{
			if (entity->getXVelocity() < entity->getSpeed())
			{
				entity->setXVelocity(entity->getAcceleration());
			}
			//entity->setNewXY(entity->getXVelocity, 0);
		}
		if (entity->getDir(2)) // move left
		{
			if (entity->getXVelocity() > entity->getSpeed()*-1)
			{
				entity->setXVelocity(entity->getAcceleration()*-1);
			}
			//entity->setNewXY(entity->getXVelocity, 0);
		}
		if (entity->getDir(3)) // move up
		{

		}
		if (entity->getDir(4)) // move down
		{

			if (entity->getYVelocity() < entity->getSpeed())
			{
				entity->setYVelocity(entity->getAcceleration());
			}

		}
	}

	entity->setNewXY
	(
		entity->getXVelocity(),
		entity->getYVelocity()
	);
}