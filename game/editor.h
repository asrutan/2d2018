// editor.h
// Alex Rutan
// 11/18/18

#ifndef EDITOR_EXIST
#define	EDITOR_EXIST

#include "basescene.h"

class Editor : public BaseScene
{
    private:

    public:
        Editor();
		Editor(Game*);
        ~Editor();
		Entity* entlist[255];
		Entity& GetPlayer();
		bool loadTextures();
		bool Init();
        int Run();
		//int End();
		void Update();
		int nextEditor = 0;
		int spawn(int);
		int despawn(Entity*);
		virtual void SaveMap(std::string name);
		virtual void LoadMap(std::string name);
		virtual void SwitchScene() {};

		//virtual void Execute();

		int entcount;
		int mousex;
		int mousey;
		int playercount;
		int enemycount;
		//bool done = false;
		bool paused = false;

		//CommandBus cbus;

		void HandleCommand(Command* command);

		//void EditorLoop();
		void EditLoop();

		unsigned int GetTime();
        
}; //end Editor

#endif //EDITOR_EXISTS
