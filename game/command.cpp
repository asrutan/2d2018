//command.cpp
//Alex Rutan
//11/12/18

#include <iostream>
#include "command.h"
#include "entity.h"
#include "console.h"
#include "player.h"

using namespace std;

JumpCommand::JumpCommand()
{
	lifetime = 1;
	cout << "created" << endl;

}

JumpCommand::JumpCommand(Entity* t_target)
{
	cout << "created" << endl;
}

void JumpCommand::Execute(Entity* t_target)
{
	//player.Jump();
	//cout << "JUMPED IN COMMAND" << endl;
	Alert("jump");
	t_target->Jump();

	cout << t_target->x << endl;
}

void JumpCommand::Execute(Player* const t_target)
{
	//player.Jump();
	//cout << "JUMPED IN COMMAND" << endl;
	Alert("jump");
	t_target->Jump();

	cout << t_target->x << endl;
}

JumpCommand jump;