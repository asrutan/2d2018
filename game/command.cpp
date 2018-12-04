//command.cpp
//Alex Rutan
//11/12/18

#include <iostream>
#include "command.h"
#include "entity.h"
#include "console.h"
#include "player.h"
#include "game.h"
#include "basescene.h"

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

void UnpauseCommand::Execute(Game * target)
{
	target->Pause();
}
bool UnpauseCommand::BExecute(Game * target)
{
	return target->Pause();
}

void QuitCommand::Execute(Game * target)
{
	target->Quit();
}

void SaveMapCommand::Execute(BaseScene * target)
{
	target->SaveMap("TestMap");
}

void LoadMapCommand::Execute(BaseScene * target)
{
	if (mapname != "") {
		target->LoadMap(mapname);
		mapname = "";
	}
}

JumpCommand jump;
UnpauseCommand unpause;
QuitCommand quit;
SaveMapCommand savemap;
LoadMapCommand loadmap;
