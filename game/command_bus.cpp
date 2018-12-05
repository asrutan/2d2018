//command_bus.cpp
//Alex Rutan
//11/13/18

#include <iostream>
#include "command_bus.h"
#include "command.h"

using namespace std;

CommandBus::CommandBus()
{
	for (int i = 0; i < COMMANDBUS_LENGTH; i++) {
		commands[i] = nullptr;
	}
}


/*
==============================Tick()===========================
Call tick to clear all commands that have already been sent.
===============================================================
*///TODO only works if one event is sent per frame.
void CommandBus::Tick()
{
	for (int i = 0; i < commandAmount; i++) {
		if (commands[i]->sent == true) {
			commandAmount--;
			commands[i] = commands[i + 1];
		}
	}
}

/*
===========================PostCommand()=======================
Add a command to the command buffer. Called by the scene or game.
===============================================================
*/
void CommandBus::PostCommand(Command * command)
{
	commands[commandAmount] = command;
	Command *newcom = command;
	command->sent = false;
	commandAmount++;
	cout << "POST COMMAND" << endl;
}

/*
===========================PostCommand()=======================
Return the command to an object which can then execute the
command. Once the command has been sent, remove it.
If there is no command in the buffer, return NULL.
===============================================================
*/
Command *CommandBus::DoCommand()
{
	if (commandAmount != 0) {
		//cout << commands[0]->sent << endl;
		commands[0]->sent = true;
		//cout << commands[0]->sent << endl;
		cout << "DO COMMAND" << endl;
		return commands[0];
	}
	return(NULL);
}
