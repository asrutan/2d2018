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
		bool jumpbutton = false;
		Game *game;

    public:
        Scene();
		Scene(Game*);
        virtual ~Scene();
		
		Entity* entlist[255];
		Entity& GetPlayer();
		int screenWidth = 800;
		int screenHeight = 600;
		bool loadTextures();
		bool Init();
		//virtual int End();
		virtual void Update();
		//void SetDone(bool t_done);
		int spawn(int);
		int despawn(Entity*);
		virtual void SaveMap(std::string name) {};
		virtual void LoadMap(std::string name);
		virtual void SwitchScene() {};
		int entcount;
		int mousex;
		int mousey;
		int playercount;
		int enemycount;
		bool paused = false;

		void HandleCommand(Command* command);

		void SceneLoop();
		void EditLoop();

		bool TimeUp();
		unsigned int GetTime();
		//virtual void SetDisplayCamera();
}; //end Scene

#endif //SCENE_EXISTS
