//collideBox.cpp
//PA
//12/6/15

#include "collideBox.h"

using namespace std;

collideBox::collideBox()
{
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}

collideBox::collideBox(int x1, int x2, int y1, int y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

int collideBox::getX1()
{
    return x1;
}

int collideBox::getX2()
{
    return x2;
}

int collideBox::getY1()
{
    return y1;
}

int collideBox::getY2()
{
    return y2;
}

void collideBox::update(int x1, int x2, int y1, int y2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

bool collideBox::contains(collideBox cBox)
{
    int testX1 = cBox.getX1();
    int testX2 = cBox.getX2();
    int testY1 = cBox.getY1();
    int testY2 = cBox.getY2();

    bool returnVal = false;

    //overlapping from bottom right
    if(x1 >= testX1 && x1 <= testX2)
	if(y1 >= testY1 && y1 <= testY2)
	    returnVal = true;
    //overlapping from bottom left
    if(x2 >= testX1 && x2 <= testX2)
	if(y1 >= testY1 && y1 <= testY2)
	    returnVal = true;
    //overlapping from top right
    if(x1 >= testX1 && x1 <= testX2)
	if(y2 >= testY1 && y2 <= testY2)
	    returnVal = true;
    //overlapping from top left
    if(x2 >= testX1 && x2 <= testX2)
	if(y2 >= testY1 && y2 <= testY2)
	    returnVal = true;
    //contains other collideBox and overlapping from bottom
    if(x1 <= testX1 && x2 >= testX2)
	if(y1 >= testY1 && y1 <= testY2)
	    returnVal = true;
    //contains other cBox and overlapping from top
    if(x1 <= testX1 && x2 >= testX2)
	if(y2 >= testY1 && y2 <= testY2)
	    returnVal = true;
    //contains other cBox and overlapping from left
    if(x1 >= testX1 && x1 <= testX2)
	if(y1 >= testY1 && y2 <= testY2)
	    returnVal = true;
    //contains other cBox and overlapping from right
    if(x2 >= testX1 && x2 <= testX2)
	if(y1 >= testY1 && y2 <= testY2)
	    returnVal = true;
    //other cBox entire contained
    if(x1 <= testX1 && x2 >= testX2)
	if(y1 >= testY1 && y2 <= testY2)
	    returnVal = true;

    return returnVal;
}
