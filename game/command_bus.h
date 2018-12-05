// command_bus.h
// Alex Rutan
// 11/13/18

#ifndef COMMANDBUS_EXIST
#define COMMANDBUS_EXIST

#define COMMANDBUS_LENGTH 255

#include "command.h"

class CommandBus{
	private:
		//int commandAmount = 0;

	public:
		CommandBus();
		~CommandBus() {}

		int commandAmount = 0;

		void Tick();
		void PostCommand(Command *command);
		Command *DoCommand();

		Command *commands[COMMANDBUS_LENGTH];
}; //end CommandBus

#endif //COMMANDBUS_EXISTS

