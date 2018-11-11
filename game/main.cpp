//main.cpp
#include <iostream>
#include "game.h"

using namespace std;

/*
  Calls an instance of game
  Initializes SDL stuff
  Runs the main game loop
  When the loop is over, safely close SDL
 */
int main(int argc, char* argv[])
{
    //cout << "Main started" << endl;
	Game game;
    //cout << "Game Made" << endl;
	if (game.Init() == 1) {
		printf("Couldn't initialize display.");
		system("pause");
		return 0;
	}
	else {
		game.LoadScene();
		game.RunScene();
	}
    //game.close();
    
    return 0;
} //end main
