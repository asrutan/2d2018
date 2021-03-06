// console.cpp
// Alex Rutan
// 11/11/18
#include <iostream>
#include "console.h"
#include "display.h"
#include "input.h"
#include "command.h"
#include "game.h"

using namespace std;
/*
/*
Console constructor 
 */
Console::Console()
{
} //end constructor

Console::Console(Display* t_display)
{
	display = t_display;
} //end constructor

Console::~Console()
{
} //end destructor

void Console::SetGame(Game * t_game)
{
	game = t_game;
}

void Console::SetDisplay(Display * t_display)
{
	display = t_display;
}

void Console::SetInput(Input * t_input)
{
	input = t_input;
}

void Console::Draw() {
	display->DrawConsole();
}

void Console::SetMessage(const char* t_message)
{
	m_cmessage = t_message;
}

void Console::SetMessage(std::string t_message)
{
	m_smessage = t_message;
}

void Console::ClearMessage()
{
	m_smessage = "";
	m_userInput = "";
}

void Console::GetInput()
{
	char letter = ' ';
	if (input->flags & IF_ENTER) {
		input->flags &= ~(IF_ENTER);
		Send();
	}
	else {
		letter = input->letterEvents();
		if (letter != NULL) {
			TypeLetter(letter);
		}
		SetMessage(m_userInput);
	}
}

void Console::TypeLetter(char c)
{
	m_userInput += c;
}

/*
============================Send()=============================
Read the message that the user has sent and determine if it's 
a valid command, then act on it.
===============================================================
*/
void Console::Send()
{
	int length = m_userInput.length();
	if (m_userInput == "jump") {
		game->ConsoleCommand(&jump);
	}
	else if (length > 5) {
		std::string load = "load ";
		std::string save = "save ";
		if (m_userInput.substr(0, 5) == load) {	
			std::string mapname = m_userInput.substr(5, length);
			//mapname.erase(remove(mapname.begin(), mapname.end(), ' '), mapname.end());
			if (mapname.length() > 0) {
				loadmap.mapname = mapname;
			}
			else {
				loadmap.mapname = "error";
			}
			game->ConsoleCommand(&loadmap);
		}
		else if(m_userInput.substr(0, 5) == save){
			std::string mapname = m_userInput.substr(5, length);
			if (mapname.length() > 0) {
				savemap.mapname = mapname;
			}
			else {
				savemap.mapname = "";
			}
			game->ConsoleCommand(&savemap);
		}
	}
	m_userInput = "";
}

const char* Console::CGetMessage()
{
	return m_cmessage;
}

std::string Console::SGetMessage()
{
	return m_smessage;
}

Console console;

/*
============================Alert()============================
Can be called from anywhere, will print to the console.
===============================================================
*/
void Alert(const char* t_string)
{
	std::string convert = t_string;
	console.SetMessage(convert);
	console.Draw();
}

void Alert(std::string t_string)
{
	cout << t_string << endl;
	console.SetMessage(t_string);
	console.Draw();
}
