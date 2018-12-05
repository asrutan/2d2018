// camera.cpp
// Alex Rutan
// 12/1/15

// Edited: 10/20/18

#include "camera.h"

using namespace std;

Camera::Camera(){
    xTarget = 0; //make target an array (not xtarg ytarg i'm just leaving this here for future reference)
    yTarget = 0;
    xVelocity = 0;
    yVelocity = 0;
    x = 0;
    y = 0;
} // end constructor

Camera::Camera(Entity *p)
{
    xTarget = 0; //make target an array (not xtarg ytarg i'm just leaving this here for future reference)
    yTarget = 0;
    xVelocity = 0;
    yVelocity = 0;
    x = 0;
    y = 0;
    //parent = p;
    campan = true;
} //end camFocus args

Camera::~Camera()
{    
} //end destructor

void Camera::Init(Entity *p) {
	printf("%d",p->x);
	parent = p;
	campan = true;
	free = false; //Whether or not the camera is parented to an entity.
}

void Camera::move()
{
    if(x == -50)
    {
	campan = false;
    }
    if(x == 50)
    {
	campan = true;
    } //end else */
    
    if(campan)
    {
        x--;
        y--;
    }
    if(campan)
    {
		x++;
        y++;
    }
} //end move

void Camera::update()
{
	/*
	If we aren't free, move to the entity minus the offset, centering the entity on the screen.
	*/
	if (!free) {
		x = parent->x - 350;
		y = parent->y - 200;
	}

	//printf("Camera x: %d\n", parent->x);

	//x = parent->x;
	//y = parent->y;
} //end update

/*camFocus::switch(target)
{

} //end switch
*/

