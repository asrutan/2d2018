// Menu.cpp
// Alex Rutan
// 11/14/18
#include <iostream>
#include "game.h"
#include "console.h"
#include "menu.h"

using namespace std;

/*
Menu constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Menu::Menu()
{

} //end constructor

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

	gui.SetDisplay(display);
	gui.CreateButton("resume", 375, 200, 50, 100, &unpause );
	gui.CreateButton("editor", 375, 300, 50, 100, &unpause );
	gui.CreateButton("quit", 375, 400, 50, 100, &quit );

	//Make scene scenebase abstract.
	gui.SetScene(this);

	return success;
}

void Menu::HandleCommand(Command* command)
{
	mcbus.PostCommand(command);
}

/*
void Menu::SetDisplayCamera() {
	display->SetCamera(camera);
}
*/
/*
First, take each of the textures and assign them to their own specific rectangles to be drawn later
Create and instance of map, map is loaded when it is constructed
Pass the map information on to player and the setEnemyMap via pointer
Create an instance of camera and send it values for number of rays and player's initial position
Create an instance of SDL_Event for player input, events change bools to "true"
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
