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
#include "display.h"

const int SPAWN = 0;
const int BULLET = 0;

class Game;
class Camera;
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
		Input *input = nullptr;
		World *world = nullptr;
		Hud *hud = nullptr;
		Gui *gui = nullptr;
		Background* background = nullptr;
		Camera *camera = nullptr;
		//bool *quit = nullptr;
		bool *editMode = nullptr;
		bool *mouseDown = nullptr;
		unsigned int currentTime = 0;
		Game *game = nullptr;

    public:
		Entity* entlist[255];
		virtual bool loadTextures() = 0;
		virtual bool Init() = 0;
		virtual void SaveMap(std::string name) = 0;
		virtual void LoadMap(std::string name) = 0;
		virtual int GetCamX() { return camera->x; };
		virtual int GetCamY() { return camera->y; };
		virtual int spawn(int entityID) = 0;
		virtual void Execute() {
			Command *command = cbus.DoCommand();
				if (command != NULL) {
					command->Execute(this);
				}
			command = nullptr;
		}
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
		virtual void SetDisplayCamera() { display->SetCamera(camera); };
        
}; //end BaseScene

#endif //BASESCENE_EXISTS
