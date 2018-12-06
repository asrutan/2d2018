// command.h
// Alex Rutan
// 11/12/18

#ifndef COMMAND_EXIST
#define COMMAND_EXIST

#define COMMAND_LENGTH 255

#include <iostream>
#include "player.h"
class Entity;
class Game;
class Command{
public:
	Command() {}
	Command(Entity* target) {}
	~Command() { std::cout << "destroyed" << std::endl; };

	bool sent = false;
	int lifetime = 0;
	int type = 0;

	const int BOOL = 1;

	Entity* target;

	virtual void Execute(Entity *target) {}
	virtual void Execute(Player *target) {}
	virtual void Execute(Game *target) {}
	virtual void Execute(BaseScene *target) {}
	virtual bool BExecute(Game *target) { return false; }
}; //end command



class JumpCommand : public Command {
	public:
		JumpCommand();
		JumpCommand(Entity* target);
		void Execute(Entity* target);
		void Execute(Player* const target);
};

class UnpauseCommand : public Command {
public:
	UnpauseCommand() {}
	void Execute(Game * target);
	bool BExecute(Game *target);
};

class QuitCommand : public Command {
public:
	QuitCommand() {}
	void Execute(Game * target);
};

class SaveMapCommand : public Command {
public:
	SaveMapCommand() {}
	SaveMapCommand(std::string name) {}
	void Execute(BaseScene * target);
	std::string mapname = "";
};

class LoadMapCommand : public Command {
public:
	LoadMapCommand() {}
	LoadMapCommand(std::string name) {}
	void Execute(BaseScene * target);
	std::string mapname = "";
};

class SwitchModeCommand : public Command {
public:
	SwitchModeCommand() {}
	SwitchModeCommand(std::string name) {}
	void Execute(Game * target);
};

class ChangeSceneCommand : public Command {
public:
	ChangeSceneCommand() { type = 1; }
	ChangeSceneCommand(std::string name) { type = 1; }
	void Execute(Game * target);
	std::string scenename = "";
};

extern JumpCommand jump;
extern UnpauseCommand unpause;
extern QuitCommand quit;
extern SaveMapCommand savemap;
extern LoadMapCommand loadmap;
extern SwitchModeCommand switchmode;
extern ChangeSceneCommand changescene;

#endif //COMMAND_EXISTS

