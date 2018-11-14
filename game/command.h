// command.h
// Alex Rutan
// 11/12/18

#ifndef COMMAND_EXIST
#define COMMAND_EXIST

#define COMMAND_LENGTH 255

#include <iostream>
#include "player.h"
class Entity;
class Command{
public:
	Command() {}
	Command(Entity* target) {}
	~Command() { std::cout << "destroyed" << std::endl; };

	bool sent = false;
	int lifetime = 0;

	Entity* target;

	virtual void Execute(Entity *target) = 0;
	virtual void Execute(Player *target) = 0;
}; //end command



class JumpCommand : public Command {
	public:
		JumpCommand();
		JumpCommand(Entity* target);
		void Execute(Entity* target);
		void Execute(Player* const target);
};
extern JumpCommand jump;

#endif //COMMAND_EXISTS

