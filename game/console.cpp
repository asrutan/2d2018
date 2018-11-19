// console.cpp
// Alex Rutan
// 11/11/18
#include <iostream>
#include "console.h"
#include "display.h"

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

void Console::SetDisplay(Display * t_display)
{
	display = t_display;
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

const char* Console::CGetMessage()
{
	return m_cmessage;
}

std::string Console::SGetMessage()
{
	return m_smessage;
}

Console console;

void Alert(const char* t_string)
{
	console.SetMessage(t_string);
	console.Draw();
}

void Alert(std::string t_string)
{
	console.SetMessage(t_string);
	console.Draw();
}
