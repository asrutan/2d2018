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
				flags |= IF_ESC;
				cout << "ESC HIT" << endl;
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				flags &= ~(IF_SPACE);
			}
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a){
				flags &= ~(IF_LEFT);
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				flags &= ~(IF_RIGHT);
			}
			if (event.key.keysym.sym == SDLK_LCTRL) {
				flags &= ~(IF_CTRL);
			}
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_TAB) {
				if (flags & IF_TAB) {
					cout << "EDIT MODE ACTIVATED" << endl;
					flags &= ~(IF_TAB);
				}
				else {
					cout << "EDIT MODE DE-ACTIVATED" << endl;
					flags |= IF_TAB;
				}
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				flags |= IF_SPACE;
			}
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a){
				flags |= IF_LEFT;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				flags |= IF_RIGHT;
			}
			if (event.key.keysym.sym == SDLK_LCTRL) {
				flags |= IF_CTRL;
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
	//return &quit;
	return false;
}

bool * Input::GetEditTogglePtr()
{
	return &editToggle;
}

bool * Input::GetMouseDownPtr()
{
	return &mouseDown;
}
