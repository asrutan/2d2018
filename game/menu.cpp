// Menu.cpp
// Alex Rutan
// 11/14/18
#include <iostream>
#include "game.h"
#include "console.h"
#include "menu.h"

using namespace std;

Menu::Menu()
{

} //end constructor

/*
==========================Menu()===============================
Gets the game and Input and Display for use
===============================================================
*/
Menu::Menu(Game *t_game)
{
	game = t_game;
	input = game->GetInput();
	display = game->GetDisplay();

} //end constructor

Menu::~Menu()
{
	delete background;
	delete camera;
	background = nullptr;
	camera = nullptr;
}

//Initialize the GUI and buttons.
bool Menu::Init(Game *t_game)
{
	bool success = true;

	game = t_game;
	input = game->GetInput();
	display = game->GetDisplay();
	camera = new Camera();

	//not setting scene of background because we do not need to update it.
	background = new Background();
	display->loadTextures("greenBackground.bmp", 3);
	display->loadTextures("resumeButt.png", 4);
	display->loadTextures("switchButt.png", 5);
	display->loadTextures("quitButt.png", 6);
	display->loadTextures("jumpButt.png", 7);

	gui.SetDisplay(display);
	gui.CreateButton("resume", 375, 200, 100, 50, &unpause );
	gui.CreateButton("editor", 375, 300, 100, 50, &switchmode );
	gui.CreateButton("quit", 375, 400, 100, 50, &quit );

	//Make scene scenebase abstract.
	gui.SetScene(this);

	return success;
}

void Menu::HandleCommand(Command* command)
{
	mcbus.PostCommand(command);
}

/*
==========================SwitchMode()=========================
When the middle button is hit, end the current scene and switch
to whichever mode we aren't on right now (edit or game).
===============================================================
*/
void Menu::SwitchMode()
{
	game->SwitchScene();
}

/*
==========================Update()============================
Draw to the screen and check to see if any of our buttons 
have been clicked
==============================================================
*/
void Menu::Update()
{
	if (input->getMouse() != 0)
	{
		gui.CheckMouse(input->mousex, input->mousey);
	}
	display->draw(background);
	gui.Update();
	mcbus.Tick();
	// end updates
}//end run
