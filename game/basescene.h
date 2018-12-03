// basescene.h
// Alex Rutan
// 12/2/18

#ifndef BASESCENE_EXIST
#define BASESCENE_EXIST

#include <string>
#include "movement.h"
#include "camera.h"
#include "background.h"
#include "collision.h"
#include "command.h"
#include "command_bus.h"
#include "gui.h"

const int SPAWN = 0;
const int BULLET = 0;

class Game;
class Display;
class Movement;
class Collision;
class Input;
class Camera;
class World;
class Hud;
class Gui;
class Entity;
class CommandBus;
class Command;

class BaseScene
{
    protected:
		Display *display = nullptr;
		Movement movement;
		Collision collision;
		Input *input = nullptr;
		Camera camera;
		World *world = nullptr;
		Hud *hud = nullptr;
		Gui *gui = nullptr;
		Background background;
		//bool *quit = nullptr;
		bool *editMode = nullptr;
		bool *mouseDown = nullptr;
		unsigned int currentTime;
		bool create = false;

		Game *game = nullptr;

    public:
		Entity* entlist[255];
		virtual bool loadTextures() = 0;
		virtual bool Init() = 0;
		int nextScene = 0;
		int screenWidth = 800;
		int screenHeight = 600;
		int entcount = 0;
		int mousex = 0;
		int mousey = 0;
		int playercount = 0;
		int enemycount = 0;
		bool done = false;
		bool paused = false;

		CommandBus cbus;

		virtual void HandleCommand(Command* command) = 0;
        
}; //end BaseScene

#endif //BASESCENE_EXISTS
