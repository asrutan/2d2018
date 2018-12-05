// game.cpp
// Alex Rutan
// 4/1/15
// mod 12/3/18
#include <iostream>
#include "game.h"
#include "console.h"
using namespace std;

 /*
 ============================Game()=============================
 Game constructor.
 Display, Input, gui, and Sound are created andtheir pointers
 are set. We pass these pointers to Scene objects.
 ===============================================================
 */
Game::Game()
{
	display = &m_display;
	input = &m_input;
	gui = &m_gui;
	sound = &m_sound;
} //end constructor

Game::~Game()
{
} //end destructor

Input * Game::GetInput()
{
	return input;
}

Display * Game::GetDisplay()
{
	return display;
}

Gui * Game::GetGui()
{
	return gui;
}

/*
============================Init()=============================
Initialize the display that we will use until the game is over.
Send a pointer to this object to the main menu and the console.
===============================================================
*/
int Game::Init() {
	if (!display->init())
	{
		return(1);
	} //end if

	//GUI
	//This adds a button in the top right of the screen.
	//When we click it, the player will jump.
	m_gui.SetDisplay(display);
	m_gui.CreateButton("button", 500, 10, 60, 60, &jump);
	//GUI

	//Pause menu
	m_menu.Init(this);
	//Pause menu

	console.SetGame(this);
	console.SetDisplay(display);
	console.SetInput(input);
	return(0);
}

/*
============================Pause()============================
If this is called, return a bool indicating whether or not the 
game is not paused. Print to the console whether or not we are 
paused. Pause/Resume the background music.
===============================================================
*/
bool Game::Pause() {
	if (m_paused) {
		m_paused = false;
		scene->SetDisplayCamera(); //Give scene camera back to scene. When paused, we get menu camera.
		Alert("unpaused");
		m_sound.resumeBGMusic();
	}
	else {
		m_paused = true;
		m_menu.SetDisplayCamera();
		Alert("paused");
		m_sound.pauseBGMusic();
	}
	return m_paused;
}

/*
============================Quit()=============================
If this is called, make the scene run it's cleanup after the 
current frame.
===============================================================
*/
void Game::Quit() {
	scene->SetDone(true);
	cout << "Quit" << endl;
}

/*
============================RunScene()=========================
Initialzies a new scene, starts the music, and runs the frame-
by-frame loop. After the loop, decide whether to switch to the
editor, load a new scene, or exit the program.
===============================================================
*/
void Game::RunScene()
{
	sceneruntimes++; //Counter for debugging purposes to see how many scenes we've loaded since the program began.
	scene->Init(); //Initialize the current scene or editor.
	m_sound.playBGMusic(); //Start the music

	/*
	Ends when the scene's done bool evaluates to true.
	Update the display. (Clear it)
	Make input read the keyboard.
	Perform high-level checks for pausing etc.
	Allow scene to perform this frame's calculations and display calls.
	Read and execute special command bus just for game.
	Draw the current frame.
	*/
	while (!scene->done) {
		/*
		====Console====
		If we are typing into the console, draw it and read the keyboard.
		*/
		if (console.active) {
			console.GetInput();
			console.Draw();
		}
		/*
		===============
		*/

		display->update();
		input->keyEvents();
		if (input->flags & IF_ESC) {
			input->flags &= ~(IF_ESC);
			scene->paused = Pause();
		}
		if (input->flags & IF_TILDE) {
			if (!console.active) {
				console.active = true;
			}
			else {
				console.active = false;
				console.ClearMessage();
			}
			input->flags &= ~(IF_TILDE);			
		}
		if (!scene->paused) {
			scene->Update();
		}
		else {
			m_menu.Update();
			Command *command = m_menu.mcbus.DoCommand();
			if (command != NULL) {
				command->Execute(this);
				scene->paused = m_paused; //Janky, a command can pause the game, account for that command.
			}
		}
		display->render(); //Draw the current frame.
	}
	/*
	If the scene ends and returns a 0, close everything and end the game.
	*/
	if (scene->End() == 0) {
		Alert("game over");
		display->GameOver();
		printf("Game over. Thanks for playing!\n");
		//system("pause");
		m_sound.stopBGMusic();
		display->close();
	}
	/*
	If the scene ends and returns a 1, load a new scene.
	*/
	else if (scene->End() == 1){
		delete this->scene;
		scene = nullptr;
		LoadScene();
		RunScene();
	}
	/*
	If the scene ends and returns a 2, get rid of the scene and switch to the editor.
	(can only evaluate true if current scene is a scene.)
	*/
	else if (scene->End() == 2) {
		delete this->scene;
		scene = nullptr;
		LoadEditor();
		RunScene();
	}
	/*
	If the scene ends and returns a 3, get rid of the editor and switch to a scene.
	(can only evaluate true if current scene is an editor.)
	*/
	else if (scene->End() == 3) {
		delete this->scene;
		scene = nullptr;
		LoadScene();
		RunScene();
	}
}

/*
============================LoadScene()========================
Instantiate a new scene and set our pointer to point to it.
Pass the pointer to our gui.
===============================================================
*/
void Game::LoadScene()
{
	scene = new Scene(this);
	m_gui.SetScene(scene);
}

/*
============================LoadEditor()========================
Instantiate a new editor and set our pointer to point to it.
Pass the pointer to our gui.
===============================================================
*/
void Game::LoadEditor()
{
	scene = new Editor(this);
	m_gui.SetScene(scene);
}

/*
============================SwitchScene()======================
Called when we want to switch the current scene to an editor
or current editor to a scene. Sets the end conditions
accordingly. End the scene.
===============================================================
*/
void Game::SwitchScene()
{
	if (m_mode == GAME) {
		m_mode = EDIT;
		nextmap = ""; //No default map to load for the editor. If we send this, it just creates a new one.
		scene->endcondition = 2;
	}
	else if (m_mode == EDIT) {
		m_mode = GAME;
		scene->endcondition = 3;
	}

	scene->SetDone(true);
}

/*
============================SetNextMap()=======================
The next scene that gets loaded, load this map for it.
===============================================================
*/
void Game::SetNextMap(std::string mapname)
{
	nextmap = mapname;
}

/*
============================GetNextMap()=======================
Return the name of the next map, used for the scene when it is
initializing.
===============================================================
*/
std::string Game::GetNextMap()
{
	return nextmap;
}

/*
============================ConsoleCommand()===================
When a valid command has been entered into the console and the
return key has been hit, take that command and send it to the 
current scene so that it may add it to the commmand bus.
===============================================================
*/
void Game::ConsoleCommand(Command *command)
{
	scene->HandleCommand(command);
}
