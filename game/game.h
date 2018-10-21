// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "display.h"
#include "camera.h"
#include "texture.h"
#include "player.h"
#include "enemy.h"
#include "entity.h"
#include "movement.h"
#include "collision.h"
#include "input.h"

class Game
{
    private:
		Display display;
		Movement movement;
		Collision collision;
		Input input;
		Camera camera;
		World *world;
		bool *quit;
		bool *editMode;
		bool *mouseDown;
		unsigned int currentTime;
		bool create = true;

    public:
        Game();
        ~Game();
		Entity* entlist[255];
		bool loadTextures();
        int run();
		int spawn(int);
		int despawn(Entity*);
		int entcount;
		int mousex;
		int mousey;
		int playercount;
		int enemycount;

		void GameLoop();
		void EditLoop();

		bool TimeUp();
		unsigned int GetTime();
        
}; //end Game

#endif //GAME_EXISTS
