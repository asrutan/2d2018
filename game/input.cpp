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
			if (event.key.keysym.sym == SDLK_BACKQUOTE) {
				flags |= IF_TILDE;
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

char Input::letterEvents()
{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_BACKQUOTE) {
					flags |= IF_TILDE;
				}
				else if (event.key.keysym.sym == SDLK_RETURN) {
					flags |= IF_ENTER;
				}

				switch (event.key.keysym.sym) {
				case SDLK_a:
					return('a');
				case SDLK_b:
					return('b');
				case SDLK_c:
					return('c');
				case SDLK_d:
					return('d');
				case SDLK_e:
					return('e');
				case SDLK_f:
					return('f');
				case SDLK_g:
					return('g');
				case SDLK_h:
					return('h');
				case SDLK_i:
					return('i');
				case SDLK_j:
					return('j');
				case SDLK_k:
					return('k');
				case SDLK_l:
					return('l');
				case SDLK_m:
					return('m');
				case SDLK_n:
					return('n');
				case SDLK_o:
					return('o');
				case SDLK_p:
					return('p');
				case SDLK_q:
					return('q');
				case SDLK_r:
					return('r');
				case SDLK_s:
					return('s');
				case SDLK_t:
					return('t');
				case SDLK_u:
					return('u');
				case SDLK_v:
					return('v');
				case SDLK_w:
					return('w');
				case SDLK_x:
					return('x');
				case SDLK_y:
					return('y');
				case SDLK_z:
					return('z');
				case SDLK_SPACE:
					return(' ');
				}
			}
		} //end if

		return(NULL);
}
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
