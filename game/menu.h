// menu.h
// Alex Rutan
// 11/14/18

#ifndef MENU_EXIST
#define MENU_EXIST

#include <SDL.h>
#include <string>

#include "scene.h"

class Game;
class Menu : public Scene
{
    private:
		//Display *display = nullptr;
		Movement movement;
		Collision collision;
		Input *input = nullptr;
		//Camera *camera = nullptr;
		World *world = nullptr;
		Hud *hud = nullptr;
		Gui gui;
		bool *editMode = nullptr;
		bool *mouseDown = nullptr;
		unsigned int currentTime;
		bool create = false;

		Game *game = nullptr;

    public:
        Menu();
		Menu(Game*);
		~Menu();
		void Update();
		bool Init(Game *game);
		void HandleCommand(Command *command);
		void SwitchMode();
		CommandBus mcbus;
		//virtual void SetDisplayCamera();

		//

		/**
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
		*/
       
}; //end Scene

#endif //SCENE_EXISTS
