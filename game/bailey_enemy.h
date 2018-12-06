// enemy.h
// Alex Rutan
// 1/3/16

#ifndef BAILEY_ENEMY_EXIST
#define BAILEY_ENEMY_EXIST

#include "collideBox.h"
#include "entity.h"

class BaileyEnemy : public Entity
{
private:
	int jumpStrength;
	const int RIGHT = 1;
	const int LEFT = 2;
	const int SCALE = 3;
	const int ROTATE = 4;
	int mode = 0;
	//int dir;

public:
	bool shrinking = false;
	BaileyEnemy();
	//Enemy(int direction);
	BaileyEnemy(int t_mode, BaseScene *scene);
	~BaileyEnemy();
	virtual void tryMove();
	virtual void move();
	virtual void update();
	void fall();
	virtual void hit();
	void checkBottom();
	bool left;
	bool right;
	int frame; //animation frame TEST
	int tick; //for animation frame TEST
}; //end Enemy

#endif //ENEMY_EXISTS
