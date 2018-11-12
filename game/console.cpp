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
	m_message = t_message;
}

const char* Console::GetMessage()
{
	return m_message;
}

Console console;

void Alert(const char* t_string)
{
	console.SetMessage(t_string);
	console.Draw();
}
