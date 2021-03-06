//movement.h
//Alex Rutan
//11/21/15

#ifndef INPUT_EXIST
#define INPUT_EXIST

#include <SDL.h>

const int IF_SPACE = 1;
const int IF_LEFTMOUSE = 2;
const int IF_LEFT = 4;
const int IF_RIGHT = 8;
const int IF_TAB = 16;
const int IF_CTRL = 32;
const int IF_ESC = 64;
const int IF_TILDE = 128;
const int IF_ENTER = 256;
const int IF_UP = 512;
const int IF_DOWN = 1024;
//Input flags
class Input
{
private:
	SDL_Event event;
	//bool escape = false;
	bool click;
	bool editToggle = false;
	bool mouseDown = false;

public:
	Input();
	~Input();

	int flags = 0;

	int mousex;
	int mousey;

	void keyEvents();
	char letterEvents();
	int getMouse();
	bool *GetQuitPtr();
	bool *GetEditTogglePtr();
	bool *GetMouseDownPtr();

}; //end Input

#endif //INPUT_EXISTS
