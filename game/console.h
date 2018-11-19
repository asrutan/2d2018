// console.h
// Alex Rutan
// 11/11/18

#ifndef CONSOLE_EXIST
#define CONSOLE_EXIST

#include <iostream>
#define testExt 69;

extern void Alert(const char* message);
extern void Alert(std::string message);

class Display;
class Console
{
	private:
		Display *display = nullptr;
		const char* m_cmessage;
		std::string m_smessage;

	public:
		Console();
		Console(Display* display);
		~Console();
		//Display* GetConsole();
		void SetDisplay(Display* display);
		void Draw();
		void SetMessage(const char* message);
		void SetMessage(std::string message);
		const char* CGetMessage();
		std::string SGetMessage();

}; //end Console

extern Console console;

#endif //CONSOLE_EXISTS
