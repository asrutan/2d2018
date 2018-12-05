// editor.cpp
// Alex Rutan
// 11/18/18
#include <iostream>
#include "player.h"
#include "game.h"
#include "console.h"
#include "editor.h"

using namespace std;

//
//
//JUST A STRIPPED DOWN SCENE
//
//


Editor::Editor()
{
	Entity *entlist = new Entity[255];
	//entlist = new Entity[255];
	entcount = 0;

} //end constructor

Editor::Editor(Game *t_game)
{
	game = t_game;
	input = game->GetInput();
	display = game->GetDisplay();
	gui = game->GetGui();
	background = new Background();
	Entity *entlist = new Entity[255];
	//entlist = new Entity[255];
	entcount = 0;
	//cout << "Scene constructed" << endl;

	//quit = false;

	//quit = input->GetQuitPtr();
	//editMode = input->GetEditTogglePtr();
	mouseDown = input->GetMouseDownPtr();

} //end constructor

Editor::~Editor()
{
	delete camera;
	camera = nullptr;
	delete[] * entlist;
} //end destructor

Entity & Editor::GetPlayer()
{
	return *entlist[0];
}

bool Editor::loadTextures()
{
	return true;
} //end loadTextures

bool Editor::Init()
{
	bool success = true;
	printf("Run number: %d \n", game->sceneruntimes);

	world = new World;
	//world->define();
	world->lines = false;
	std::string map = game->GetNextMap();
	if (map == "") {
		world->CreateNew();
	}
	else {
		world->Load(map);
	}

	//Load background based on world info
	background->SetScene(this);

	camera = new Camera();

	SetDisplayCamera();

	*mouseDown = false;

	return success;
}

int Editor::spawn(int entid)
{
	if (entid == 0)
	{
		//entlist[entcount] = new Entity(&currentTime, 0);
		//*entlist[entcount] = entlist[entcount]->NewPlayer();
		entlist[entcount] = new Player(&currentTime);
		entlist[entcount]->setListID(entcount);
		entcount++;

		return 0;
	}
	else if (entid == 1)
	{
		entlist[entcount] = new Enemy(1, this);
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(mousex, mousey);
		entcount++;
		return 0;
	}
	else if (entid == 2)
	{
		entlist[entcount] = new Enemy(2, this);
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(mousex, mousey);
		entcount++;
		return 0;
	}
	else if (entid == 3) {
		if (entlist[0]->direction == 0) {
			entlist[entcount] = new Enemy(2, this);
			entlist[entcount]->setXY(entlist[0]->x - 60, entlist[0]->y);
		}
		else {
			entlist[entcount] = new Enemy(1, this);
			entlist[entcount]->setXY(entlist[0]->x + 100, entlist[0]->y);
		}
		entlist[entcount]->setListID(entcount);
		entcount++;
		return 0;
	}
	//Scale Demo
	else if (entid == 4) {
		entlist[entcount] = new Enemy(3, this);
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(700, 250);
		entcount++;
		return 0;
	}
	//Rotate Demo
	else if (entid == 5) {
		entlist[entcount] = new Enemy(4, this);
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(100, 250);
		entcount++;
		return 0;
	}
	else { cout << "can't spawn entity" << endl; return 0; }
} //end spawn

int Editor::despawn(Entity* entity)
{
	if (entcount < 1) { cout << "nothing to despawn" << endl;  return 0; }

	int old = entity->getListID();
	int right = entcount - old;

	if (old < entcount)
	{
		delete entity;
		entity = NULL;
		for (int i = old; i < entcount - 1; i++)
		{
			entlist[i] = entlist[i + 1];
			entlist[i]->setListID(i);
		}
		entcount--;
		return 0;
	}
	else if (entity->getListID() == entcount)
	{
		delete entity;
		entity = NULL;
		entcount--;
		return 0;
	}
	else { cout << "can't despawn entity" << endl; return 0; }
} //end spawn

unsigned int Editor::GetTime()
{
	return SDL_GetTicks();
}

/*
void Scene::SetDisplayCamera()
{
display->SetCamera(&camera);
}
*/

void Editor::SaveMap(std::string t_name) {
	const char* name = t_name.c_str();
	printf("Saving: %s\n", name);
	world->SaveToFile(t_name);
}

void Editor::LoadMap(std::string t_name){
	const char* name = t_name.c_str();
	if (world->CheckExist(name)) {
		printf("Loaded: %s\n", name);
		endcondition = 2;
		game->SetNextMap(t_name);
		done = true;
	}
	else {
		printf("Map '%s' does not exist!\n", name);
	}
}
void Editor::HandleCommand(Command* command)
{
	cbus.PostCommand(command);
}

void Editor::EditLoop() {
	//input->keyEvents();
	mousex = input->mousex + camera->x;
	mousey = input->mousey + camera->y;
	if (input->getMouse() != 0) {
		world->CreateBrush(mousex, mousey);
	} //end if

	if (*mouseDown) {
		world->EditBrush(mousex, mousey);
	}
	else {
		world->NormalizeBrush();
	}
}

void Editor::Update()
{
	currentTime = SDL_GetTicks();

	Execute();

	if (input->flags & IF_LEFT) {
		camera->x -= 10;
	}
	if (input->flags & IF_RIGHT) {
		camera->x += 10;
	}
	if (input->flags & IF_UP) {
		camera->y -= 10;
	}
	if (input->flags & IF_DOWN) {
		camera->y += 10;
	}

	EditLoop();

	//entlist[0]->update();
	camera->update();
	/**************/
	//movement.move(entlist[0]); //move, checkbounds, update

	//skeleton
	//Act(entlist[0]->SceneRequest());
	//display->update(); // background and clear

	if (entcount > 0) {
		for (int i = 0; i < entcount; i++) {
			if (i != 0)entlist[i]->update(); //if collide, do not update to newX/newY
			if (entlist[i]->getIsDead())despawn(entlist[i]);
		} //update entities
		  /**************/
	}

	background->Update();
	display->draw(background);

	if (entcount > 0) {
		for (int i = 0; i < entcount; i++) {
			display->draw(entlist[i]);
		}
	}

	display->draw(world);

	gui->Update();

	cbus.Tick();

	//display->render(); //draw to screen

	// end updates
}
/*
void Editor::SetDone(bool t_done)
{
	done = t_done;
}
//end run
*/
/*
void Scene::SetDisplayCamera() {
display->SetCamera(camera);
}
*/

