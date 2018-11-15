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

//Call tick to clear all commands that have already been sent.
//TODO only works if one event is sent per frame.
void CommandBus::Tick()
{
	for (int i = 0; i < commandAmount; i++) {
		if (commands[i]->sent == true) {
			commandAmount--;
			commands[i] = commands[i + 1];
		}
	}
}

void CommandBus::PostCommand(Command * command)
{
	commands[commandAmount] = command;
	Command *newcom = command;
	command->sent = false;
	commandAmount++;
}

Command *CommandBus::DoCommand()
{
	if (commandAmount != 0) {
		cout << commands[0]->sent << endl;
		commands[0]->sent = true;
		cout << commands[0]->sent << endl;

		return commands[0];
	}
	return(NULL);
}
