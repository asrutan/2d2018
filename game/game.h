// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include "scene.h"
#include "display.h"
#include "gui.h"
#include "input.h"
#include "menu.h"

class Game
{
    private:
		Scene *scene;
		Display m_display;
		Input m_input;
		Gui m_gui;
		Menu m_menu;
		//Console m_console;
		
		Display *display = nullptr;
		Input *input = nullptr;
		Gui *gui = nullptr;
		//Console *console = nullptr;

		bool m_paused = false;

    public:
        Game();
        ~Game();

		Input* GetInput();
		Display* GetDisplay();
		Gui* GetGui();

		bool Pause();
		void Quit();
		int Init();
		void RunScene();
		void LoadScene();

		void ConsoleCommand(Command *command);

		int sceneruntimes;
        
}; //end Game

#endif //GAME_EXISTS
