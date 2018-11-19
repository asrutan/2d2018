// editor.h
// Alex Rutan
// 11/18/18

#ifndef EDITOR_EXIST
#define	EDITOR_EXIST

#include <SDL.h>
#include <string>
#include "display.h"
#include "camera.h"
#include "texture.h"
#include "entity.h"
#include "player.h"
#include "movement.h"
#include "collision.h"
#include "input.h"
#include "hud.h"
#include "gui.h"
#include "command.h"
#include "command_bus.h"

//const int SPAWN = 0;
//const int BULLET = 0;

class Game;
class Editor
{
    private:
		Display *display;
		Movement movement;
		Input *input;
		Camera camera;
		World *world;
		Hud *hud;
		Gui *gui = nullptr;
		bool *quit;
		bool *editMode;
		bool *mouseDown;
		unsigned int currentTime;
		bool create = false;

		Game *game;

    public:
        Editor();
		Editor(Game*);
        ~Editor();
		Entity* entlist[255];
		Entity& GetPlayer();
		bool loadTextures();
		bool Init();
        int Run();
		int End();
		void Update();
		void SetDone(bool done);
		int nextEditor = 0;
		int spawn(int);
		int despawn(Entity*);
		int entcount;
		int mousex;
		int mousey;
		int playercount;
		int enemycount;
		bool done = false;
		bool paused = false;

		CommandBus cbus;

		void HandleCommand(Command* command);

		void EditorLoop();
		void EditLoop();

		unsigned int GetTime();
        
}; //end Editor

#endif //EDITOR_EXISTS
