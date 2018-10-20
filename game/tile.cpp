//tile.cpp
//PA
//11/22/15

#include <iostream>
#include "tile.h"

using namespace std;

Tile::Tile()
{
    myTexture = NULL;
    tileW = 50;
    tileH = 50;
    posX = 0;
    posY = 0;
    myTag = 1;
    cBox = collideBox(posX, posX + tileW, posY, posY + tileH);
}

/*
Tile::Tile(Display* d, int x, int y, int tag)
{
    display = d;
    tileW = 50;
    tileH = 50;
    posX = x;
    posY = y;
    myTag = tag;
    texture = Texture(display);
    cBox = collideBox(posX, posX + tileW, posY, posY + tileH);
    myTexture = NULL;
}
*/

Tile::~Tile()
{
}

int Tile::getTileWidth()
{
    return tileW;
}

int Tile::getTileHeight()
{
    return tileH;
}

int Tile::getXPos()
{
    return posX;
}

int Tile::getYPos()
{
    return posY;
}

int Tile::getTag()
{
    return myTag;
}

void Tile::setXPos(int x)
{
    posX = x;
}

void Tile::setYPos(int y)
{
    posY = y;
}

void Tile::setTag(int tag)
{
    myTag = tag;
}

collideBox Tile::getCollideBox()
{
    return cBox;
}

bool Tile::textureTile(string path)
{
    bool success = true;
    if(!texture.makeTexture(path))
    {
	success = false;
    }
    else
    {
        myTexture = texture.getTexture();
    }
    return success;
}

SDL_Texture* Tile::getTexture()
{
    return myTexture;
}
