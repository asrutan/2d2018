// scene.h
// Alex Rutan
// 11/10/18

#ifndef SCENE_EXIST
#define SCENE_EXIST

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

const int SPAWN = 0;
const int BULLET = 0;

class Game;
class Scene
{
    private:
		Display *display;
		Movement movement;
		Collision collision;
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
        Scene();
		Scene(Game*);
        ~Scene();
		Entity* entlist[255];
		Entity& GetPlayer();
		bool loadTextures();
		bool Init();
        int Run();
		int End();
		void Update();
		void SetDone(bool done);
		int nextScene = 0;
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

		void Act(int request);

		void SceneLoop();
		void EditLoop();

		bool TimeUp();
		unsigned int GetTime();
        
}; //end Scene

#endif //SCENE_EXISTS
