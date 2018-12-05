// collision.cpp
// PA
// Alex Rutan
// 12/01/15
// mod 10/16/17

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

//Check for collisions between two entities, tell them they've collided.
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

//Check collision between an entity and a horizontal line.
void Collision::checkBounds(Entity * entity1, World::horizontal* horizont)
{
	if (entity1->y + entity1->height > horizont->y) // bottom collide
	{
		if (entity1->x + entity1->width > horizont->x1 && entity1->x < horizont->x2)
		{
			entity1->onGround = true;
		}
		else(entity1->onGround = false);
	}
}

//Check collision between an entity and a vertical line.
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

//Check collision between an entity and a brush.
void Collision::checkBounds(Entity *entity1, Brush *brush)
{
	if (entity1->x + entity1->width > brush->x && entity1->x < brush->x) // right side collide
	{
		if (entity1->y < brush->y + brush->h && entity1->y + entity1->height > brush->y)
		{
			//entity1->collided[brush->type] = true; //behavior upon collision is determined by the type of entity it hits.
			//brush->collided[entity1->getEntityID()] = true;
			//cout << "right" << endl;
		}
	}

	if (entity1->x < brush->x + brush->w && entity1->x + entity1->width > brush->x + brush->w) // left side collide
	{
		if (entity1->y < brush->y + brush->h && entity1->y + entity1->height > brush->y)
		{
			//entity1->collided[brush->type] = true; //behavior upon collision is determined by the type of entity it hits.
			//brush->collided[entity1->getEntityID()] = true;
			//cout << "left" << endl;
		}
	}

	if (entity1->y < brush->y + brush->h && entity1->y + entity1->height > brush->y + brush->h) // top collide
	{
		if (entity1->x + entity1->width > brush->x && entity1->x < brush->x + brush->w)
		{
			//entity1->collided[brush->type] = true; //behavior upon collision is determined by the type of entity it hits.
			//brush->collided[entity1->getEntityID()] = true;
			//cout << "top" << endl;
		}
	}

	//start false every frame.
	entity1->onGround = false;
	if (entity1->y + entity1->height >= brush->y && entity1->y <= brush->y) // bottom collide
	{
		if (entity1->x + entity1->width >= brush->x && entity1->x <= brush->x + brush->w)
		{
			entity1->setYVelocity(0);
			entity1->y = brush->y - entity1->height;
			entity1->onGround = true; //behavior upon collision is determined by the type of entity it hits.
			//cout << "bottom" << endl;
		}
	}
}

//Check collision between an entity and a given point.
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


