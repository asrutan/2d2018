// bailey_scene.h
// Bailey Dishman
// 12/5/2018

#ifndef BAILEY_SCENE_EXIST
#define BAILEY_SCENE_EXIST

#include <string>
#include "basescene.h"
#include "bailey_player.h"
#include "player.h"

class BaileyScene : public BaseScene
{

	protected:

		Movement movement;
		Collision collision;
		Input *input;
		World *world;
		Hud *hud;
		Gui *gui = nullptr;
		Background *background;
		bool *editMode;
		bool *mouseDown;
		bool create = false;

		Game *game;

	public:

		BaileyScene();
		BaileyScene(Game*);
		~BaileyScene();

		Entity* entlist[255];
		Entity* baileyEnemyList[255];
		Entity& GetPlayer();
		int screenWidth = 800;
		int screenHeight = 600;
		bool loadTextures();
		bool Init();
		virtual void Update();
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

		int typecount = 1;

		void HandleCommand(Command* command);

		void SceneLoop();
		void EditLoop();

		bool TimeUp();
		unsigned int GetTime();

		int randNum();

}; //end Scene

#endif //SCENE_EXISTS
