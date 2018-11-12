// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include "scene.h"
#include "display.h"
#include "input.h"

class Game
{
    private:
		Scene *scene;
		Display m_display;
		Input m_input;
		//Console m_console;

		Display *display = nullptr;
		Input *input = nullptr;
		//Console *console = nullptr;

    public:
        Game();
        ~Game();

		Input* GetInput();
		Display* GetDisplay();

		int Init();
		void RunScene();
		void LoadScene();

		int sceneruntimes;
        
}; //end Game

#endif //GAME_EXISTS
