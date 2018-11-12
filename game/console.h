// console.h
// Alex Rutan
// 11/11/18

#ifndef CONSOLE_EXIST
#define CONSOLE_EXIST

#include <iostream>
#define testExt 69;

extern void Alert(char* message);

class Display;
class Console
{
	private:
		Display *display = nullptr;
		char* m_message = 0;

	public:
		Console();
		Console(Display* display);
		~Console();
		//Display* GetConsole();
		void SetDisplay(Display* display);
		void Draw();
		void SetMessage(char* message);
		char* GetMessage();

}; //end Console

extern Console console;

#endif //CONSOLE_EXISTS
