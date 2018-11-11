// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include "game.h"

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

int Game::Init() {
	if (!display->init())
	{
		//("Couldn't initialize display.");
		return(1);
	} //end if
	return(0);
}

void Game::RunScene()
{
	sceneruntimes++;
	if (scene->Run() == 0) {
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
}