// tile.h
// PA
// 11/22/15

#ifndef TILE_EXIST
#define TILE_EXIST

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "texture.h"
#include "collideBox.h"

class Tile
{
    private:
       Texture texture;
       SDL_Texture* myTexture;
       //Display* display;
       int tileW;
       int tileH;
       int posX;
       int posY;
       int myTag;
       collideBox cBox;
    public:
       Tile();
       //Tile(Display*, int, int, int);
       ~Tile();
       int getTileWidth();
       int getTileHeight();
       int getXPos();
       int getYPos();
       int getTag();
       collideBox getCollideBox();
       void setXPos(int);
       void setYPos(int);
       void setTag(int);
       bool textureTile(std::string);
       SDL_Texture* getTexture();
};

#endif
