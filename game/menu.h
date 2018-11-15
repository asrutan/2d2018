// menu.h
// Alex Rutan
// 11/14/18

#ifndef MENU_EXIST
#define MENU_EXIST

#include <SDL.h>
#include <string>

#include "scene.h"

class Game;
class Menu
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
		bool *quit;
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
       
}; //end Scene

#endif //SCENE_EXISTS
