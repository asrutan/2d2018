// collision.cpp
// PA
// 12/01/15

#include <iostream>
#include "collision.h"

using namespace std;

Collision::Collision()
{

}


Collision::~Collision()
{

}

//WORKING

void Collision::checkBounds(Entity * entity1, Entity * entity2)
{
	if (entity1->x + entity1->width > entity2->x && entity1->x < entity2->x) // right side collide
	{
		if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y)
		{
			entity1->collided[entity2->getEntityID()] = true; //behavior upon collision is determined by the type of entity it hits.
			entity2->collided[entity1->getEntityID()] = true;
			//cout << "right" << endl;
		}
	}

	if (entity1->x < entity2->x + entity2->width && entity1->x + entity1->width > entity2->x + entity2->width) // left side collide
	{
		if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y)
		{
			entity1->collided[entity2->getEntityID()] = true; //behavior upon collision is determined by the type of entity it hits.
			entity2->collided[entity1->getEntityID()] = true;
			//cout << "left" << endl;
		}
	}

	if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y + entity2->height) // top collide
	{
		if (entity1->x + entity1->width > entity2->x && entity1->x < entity2->x + entity2->width)
		{
			entity1->collided[entity2->getEntityID()] = true; //behavior upon collision is determined by the type of entity it hits.
			entity2->collided[entity1->getEntityID()] = true;
			//cout << "top" << endl;
		}
	}

	if (entity1->y + entity1->height > entity2->y && entity1->y < entity2->y) // bottom collide
	{
		if (entity1->x + entity1->width > entity2->x && entity1->x < entity2->x + entity2->width)
		{
			entity1->collided[entity2->getEntityID()] = true; //behavior upon collision is determined by the type of entity it hits.
			entity2->collided[entity1->getEntityID()] = true;
			//cout << "bottom" << endl;
		}
	}
}


/*
//EXPERIMENTAL
void Collision::checkBounds(Entity * entity1, Entity * entity2)
{
	if (entity1->x + entity1->width > entity2->x && entity1->x < entity2->x) // right side collide
	{
		if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y)
		{
			entity1->collided = true;
			entity2->collided = true;
			cout << "right" << endl;
		}
	}

	else if (entity1->x < entity2->x + entity2->width && entity1->x + entity1->width > entity2->x + entity2->width) // left side collide
	{
		if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y)
		{
			entity1->collided = true;
			entity2->collided = true;
			cout << "left" << endl;
		}
	}

	if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y + entity2->height) // top collide
	{
		if (entity1->x + entity1->width > entity2->x && entity1->x < entity2->x + entity2->width)
		{
			entity1->collided = true;
			entity2->collided = true;
			cout << "top" << endl;
			if (entity1->x >= entity2->x)(entity1->collideSide[1] = true, cout << "leftHit" << endl);
			if (entity1->x <= entity2->x)(entity1->collideSide[0] = true, cout << "rightHit" << endl);
			if (entity1->y >= entity2->y)(entity1->collideSide[3] = true, cout << "topHit" << endl);
		}
	}

	if (entity1->y + entity1->height > entity2->y && entity1->y < entity2->y) // bottom collide
	{
		if (entity1->x + entity1->width > entity2->x && entity1->x < entity2->x + entity2->width)
		{
			entity1->collided = true;
			entity2->collided = true;
			//cout << "bottom" << endl;
			if (entity1->y >= entity2->y)(entity1->collideSide[4] = true, cout << "bottom" << endl);
		}
	}
}*/

void Collision::checkBounds(Entity * entity1, World::horizontal* horizont)
{
	if (entity1->y + entity1->height > horizont->y) // bottom collide
	{
		if (entity1->x + entity1->width > horizont->x1 && entity1->x < horizont->x2)
		{
			entity1->floorHit = true;
		}
		else(entity1->floorHit = false);
	}
}

void Collision::checkBounds(Entity * entity1, World::vertical* vert)
{
	if (entity1->x + entity1->width > vert->x) // side collide
	{
		if (entity1->x + entity1->width > vert->x && entity1->x < vert->x) // right side collide
		{
			//cout << "wubba" << endl;
			if (entity1->y > vert->y1 && entity1->y + entity1->height < vert->y2)
			{
				entity1->collided[1] = true;
				//cout << "wall" << endl;
				//cout << "right" << endl;
			}
		}

		//if (entity1->x < entity2->x + entity2->width && entity1->x + entity1->width > entity2->x + entity2->width) // left side collide
		//{
		//	if (entity1->y < entity2->y + entity2->height && entity1->y + entity1->height > entity2->y)
		//	{
		//		entity1->collided = true;
		//		entity2->collided = true;
				//cout << "left" << endl;
		//	}
		//}
		else(entity1->wallHit = false);
	}
}


void Collision::checkBounds(Entity * entity1, int x, int y)
{
	if (entity1->x + entity1->width > x && entity1->x < x) // right side collide
	{
		if (entity1->y < y + entity1->height && entity1->y + entity1->height > y)
		{
			entity1->collided[1] = true;
		}
	}

	if (entity1->x < x + entity1->width && entity1->x + entity1->width > x + entity1->width) // left side collide
	{
		if (entity1->y < y + entity1->height && entity1->y + entity1->height > y)
		{
			entity1->collided[1] = true;
		}
	}
}


