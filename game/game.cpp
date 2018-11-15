// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include "game.h"
#include "console.h"
using namespace std;

/*
Game constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Game::Game()
{
	display = &m_display;
	input = &m_input;
	gui = &m_gui;
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

int Game::Init() {
	if (!display->init())
	{
		//("Couldn't initialize display.");
		return(1);
	} //end if

	//GUI
	m_gui.SetDisplay(display);
	m_gui.CreateButton("button", 500, 10, 60, 60, &jump);
	//GUI

	//Pause menu
	m_menu.Init(this);
	//Pause menu

	console.SetDisplay(display);
	return(0);
}

bool Game::Pause() {
	if (m_paused) {
		m_paused = false;
		Alert("unpaused");
	}
	else {
		m_paused = true;
		Alert("paused");
	}
	return m_paused;
}

void Game::RunScene()
{
	sceneruntimes++;
	/*
	if (scene->Run() == 0) {
		Alert("game over");
		display->GameOver();
		printf("Game over. Thanks for playing!\n");
		system("pause");

		display->close();
	}
	else {
		printf("New Scene\n");
		delete this->scene;
		scene = nullptr;
		LoadScene();
		RunScene();
	}
	*/
	scene->Init();
	while (!scene->done) {
		display->update();
		input->keyEvents();
		if (input->flags & IF_SPACE) {
			input->flags &= ~(IF_SPACE);
			scene->paused = Pause();
		}
		if (!scene->paused) {
			scene->Update();
		}
		else {
			m_menu.Update();
			Command *command = m_menu.mcbus.DoCommand();
			if (command != NULL) {
				scene->paused = command->BExecute(this);		
			}
		}
		display->render();
	}
	if (scene->End() == 0) {
		Alert("game over");
		display->GameOver();
		printf("Game over. Thanks for playing!\n");
		system("pause");

		display->close();
	}
	else {
		printf("New Scene\n");
		delete this->scene;
		scene = nullptr;
		LoadScene();
		RunScene();
	}
}

void Game::LoadScene()
{
	scene = new Scene(this);
	m_gui.SetScene(scene);
	//testExt = 69;
	//int sixtynine = testExt;
	//cout << sixtynine << endl;
	Alert("No game no life");
}