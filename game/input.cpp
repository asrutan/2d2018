// input.cpp
// Alex Rutan
// 10/19/17
#include <iostream>
#include "input.h"

using namespace std;

Input::Input()
{
	SDL_Event event;
} //end constructor

Input::~Input()
{
} //end destructor

void Input::keyEvents()
{
	while (SDL_PollEvent(&event) != 0)
	{
		SDL_GetMouseState(&mousex, &mousey);
		if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0){
			click = true;
			mouseDown = true;
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			mouseDown = false;
		}
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
				cout << "QUIT HIT" << endl;
			}
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_SPACE) {
				if (editToggle) {
					editToggle = false;
					cout << "EDIT MODE DE-ACTIVATED" << endl;
				}
				else {
					editToggle = true;
					cout << "EDIT MODE ACTIVATED" << endl;
				}
			}
		}
	} //end if
} //end while
  //end keyEvents

int Input::getMouse()
{
	if (click)
	{
		click = false;
		return(mousex, mousey);
	}
	else return 0;
}

bool * Input::GetQuitPtr()
{
	return &quit;
}

bool * Input::GetEditTogglePtr()
{
	return &editToggle;
}

bool * Input::GetMouseDownPtr()
{
	return &mouseDown;
}
