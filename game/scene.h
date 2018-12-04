// scene.h
// Alex Rutan
// 11/10/18

#ifndef SCENE_EXIST
#define SCENE_EXIST

#include <string>
#include "basescene.h"

class Scene : public BaseScene
{
    protected:	
		//Display *display;
		Movement movement;
		Collision collision;
		Input *input;
		//Camera *camera;
		World *world;
		Hud *hud;
		Gui *gui = nullptr;
		Background *background;
		//bool *quit;
		bool *editMode;
		bool *mouseDown;
		bool create = false;

		Game *game;

    public:
        Scene();
		Scene(Game*);
        ~Scene();
		
		Entity* entlist[255];
		Entity& GetPlayer();
		int screenWidth = 800;
		int screenHeight = 600;
		bool loadTextures();
		bool Init();
		int End();
		void Update();
		void SetDone(bool done);
		int endcondition = 0;
		int spawn(int);
		int despawn(Entity*);
		virtual void SaveMap(std::string name) {};
		virtual void LoadMap(std::string name);
		int entcount;
		int mousex;
		int mousey;
		int playercount;
		int enemycount;
		bool done = false;
		bool paused = false;

		void HandleCommand(Command* command);

		void SceneLoop();
		void EditLoop();

		bool TimeUp();
		unsigned int GetTime();
		//virtual void SetDisplayCamera();
}; //end Scene

#endif //SCENE_EXISTS
