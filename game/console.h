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
class Input;
class Game;
class Console
{
	private:
		Game *game = nullptr;
		Display *display = nullptr;
		Input *input = nullptr;
		const char* m_cmessage;
		std::string m_smessage;
		std::string m_userInput = "";

	public:
		Console();
		Console(Display* display);
		~Console();
		//Display* GetConsole();
		bool active = false;
		void SetGame(Game* game);
		void SetDisplay(Display* display);
		void SetInput(Input* input);
		void Draw();
		void SetMessage(const char* message);
		void SetMessage(std::string message);
		void ClearMessage();
		void GetInput();
		void TypeLetter(char c);
		void Send();
		const char* CGetMessage();
		std::string SGetMessage();

}; //end Console

extern Console console;

#endif //CONSOLE_EXISTS
