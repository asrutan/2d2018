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

/*
=======================JumpCommand::Execute()==================
Tells the target entity to perform a jump.
===============================================================
*/
void JumpCommand::Execute(Entity* t_target)
{
	Alert("jump"); // Print in the console
	t_target->Jump();
}

/*
=======================JumpCommand::Execute()==================
Tells the target palyer to perform a jump.
===============================================================
*/
void JumpCommand::Execute(Player* const t_target)
{
	Alert("jump"); // Print in the console
	t_target->Jump();
}

/*
======================UnpauseCommand::Execute()================
Pause the game.
===============================================================
*/
void UnpauseCommand::Execute(Game * target)
{
	target->Pause();
}
/*
======================UnpauseCommand::BExecute()===============
Pause the game. Return a bool indicating whether or not the game
is paused or unpaused.
===============================================================
*/
bool UnpauseCommand::BExecute(Game * target)
{
	return target->Pause();
}

/*
======================QuitCommand::Execute()===================
Quit the game.
===============================================================
*/
void QuitCommand::Execute(Game * target)
{
	target->Quit();
}

/*
======================SaveMapCommand::Execute()================
Save the current map to a file if the name isn't empty. Set to
empty name so it doesn't get carried over for the next call to
this command.
===============================================================
*/
void SaveMapCommand::Execute(BaseScene * target)
{
	if (mapname != "") {
		target->SaveMap(mapname);
		mapname = "";
	}
}

/*
======================LoadMapCommand::Execute()================
If the mapname isn't empty, load the map into the scene. Set to
empty name so it doesn't get carried over for the next call to
this command.
===============================================================
*/
void LoadMapCommand::Execute(BaseScene * target)
{
	if (mapname != "") {		
		target->LoadMap(mapname);
		mapname = "";
	}
}

/*
====================SwitchModeCommand::Execute()===============
Tell the game to end the current scene and switch from editor to
scene or vice-versa.
===============================================================
*/
void SwitchModeCommand::Execute(Game * target)
{
	//End and switch to opposite mode.
	target->SwitchScene();
}

/*
==================ChangeSceneCommand::Execute()================
If the mapname isn't empty, load the map into the scene. Set to
empty name so it doesn't get carried over for the next call to
this command.
===============================================================
*/
void ChangeSceneCommand::Execute(Game* target)
{
	if (scenename != "") {
		target->ChangeScene(scenename);
		scenename = "";
	}
}

//Globals so they can be referenced anywhere.
JumpCommand jump;
UnpauseCommand unpause;
QuitCommand quit;
SaveMapCommand savemap;
LoadMapCommand loadmap;
SwitchModeCommand switchmode;
ChangeSceneCommand changescene;