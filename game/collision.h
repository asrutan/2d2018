// collision.h
// PA
// 12/01/15

#ifndef COLLISION_EXIST
#define COLLISION_EXIST

#include "entity.h"
#include "world.h"

class Collision
{
  private:
    int playerX;
    int playerY;

  public:
    Collision();
    ~Collision();
    
	void checkBounds(Entity* entity1, Entity* entity2);
	void checkBounds(Entity * entity1, World*);
	void checkBounds(Entity* entity1, World::horizontal*);
	void checkBounds(Entity* entity1, World::vertical*);
	void checkBounds(Entity* entity1, Brush*);
	void checkBounds(Entity* entity1, int x, int y);
};

#endif
