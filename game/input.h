//movement.h
//Alex Rutan
//11/21/15

#ifndef INPUT_EXIST
#define INPUT_EXIST

#include <SDL.h>

class Input
{
private:
	SDL_Event event;
	bool quit = false;
	bool click;
	bool editToggle = false;
	bool mouseDown = false;

public:
	Input();
	~Input();

	int mousex;
	int mousey;

	void keyEvents();
	int getMouse();
	bool *GetQuitPtr();
	bool *GetEditTogglePtr();
	bool *GetMouseDownPtr();

}; //end Input

#endif //INPUT_EXISTS
