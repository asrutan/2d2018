// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include "scene.h"
#include "basescene.h"
#include "editor.h"
#include "display.h"
#include "gui.h"
#include "input.h"
#include "menu.h"
#include "sound.h"

#include "bailey_scene.h"

class Game
{

    private:

		BaseScene *scene;
		Editor *editor;
		Sound m_sound;
		Display m_display;
		Input m_input;
		Gui m_gui;
		Menu m_menu;
		//Console m_console;
		
		Display *display = nullptr;
		Input *input = nullptr;
		Gui *gui = nullptr;
		Sound *sound = nullptr;
		//Console *console = nullptr;

		bool m_paused = false;

		const int GAME = 0;
		const int EDIT = 1;
		int m_mode = GAME;

		std::string nextmap = "demomap";
		std::string nextscene = "demo"; // SWITCH BACK TO DEMO ONCE TESTS ARE DONE

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
		void LoadEditor();
		void SwitchScene();
		void SetNextMap(std::string mapname);
		void ChangeScene(std::string scenename);
		std::string GetNextMap();

		void ConsoleCommand(Command *command);

		int sceneruntimes;
        
}; //end Game

#endif //GAME_EXISTS
