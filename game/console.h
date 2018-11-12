// console.h
// Alex Rutan
// 11/11/18

#ifndef CONSOLE_EXIST
#define CONSOLE_EXIST

#include <iostream>
#define testExt 69;

extern void Alert(const char* message);

class Display;
class Console
{
	private:
		Display *display = nullptr;
		const char* m_message;

	public:
		Console();
		Console(Display* display);
		~Console();
		//Display* GetConsole();
		void SetDisplay(Display* display);
		void Draw();
		void SetMessage(const char* message);
		const char* GetMessage();

}; //end Console

extern Console console;

#endif //CONSOLE_EXISTS
