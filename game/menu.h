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
		Display *display;
		Movement movement;
		Collision collision;
		Input *input;
		Camera camera;
		World *world;
		Hud *hud;
		Gui gui;
		bool *editMode;
		bool *mouseDown;
		unsigned int currentTime;
		bool create = false;

		Game *game;

    public:
        Menu();
		Menu(Game*);
		~Menu() {}
		void Update();
		bool Init(Game *game);
		void HandleCommand(Command *command);
		CommandBus mcbus;

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
