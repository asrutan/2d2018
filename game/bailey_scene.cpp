// bailey_scene.cpp
// Bailey Dishman
// 12/5/2018

#include "bailey_scene.h"

#include <iostream>
#include <cstdlib>
#include <time.h> 
#include "scene.h"
#include "game.h"
#include "console.h"
#include "hud.h"

using namespace std;

BaileyScene::BaileyScene()
{

	Entity *entlist = new Entity[255];
	entcount = 0;

} 

/*
==========================BaileyScene()========================
Scene constructor that takes a pointer to the game that
instantiated it.
Gets pointers to:
Game, Input, Display, Gui, Background.
Initializes list of entites.
===============================================================
*/
BaileyScene::BaileyScene(Game *t_game)
{
	game = t_game;
	input = game->GetInput();
	display = game->GetDisplay();
	gui = game->GetGui();
	background = new Background();
	Entity *entlist = new Entity[255];
	entcount = 0;

	editMode = input->GetEditTogglePtr();
	mouseDown = input->GetMouseDownPtr();

} //end constructor

BaileyScene::~BaileyScene()
{

	delete camera;
	camera = nullptr;
	delete[] * entlist;

} //end destructor

Entity & BaileyScene::GetPlayer()
{
	return *entlist[0]; //player is always at first spot in list
}

//Moved to display
bool BaileyScene::loadTextures()
{

	return true;

} //end loadTextures

/*
============================Init()=============================
Initializes the world and runs the map that is dictated by the
game. Loads all of the textures we will use into memory on
the display. Creates a camera and sets it in display as the
current camera. Spawns the player and test entities.
===============================================================
*/
bool BaileyScene::Init()
{
	bool success = true;
	printf("Run number: %d \n", game->sceneruntimes);

	world = new World;
	world->define();
	world->lines = false;
	world->Load(game->GetNextMap());

	//Load background based on world info
	background->SetScene(this);

	display->loadTextures("robot.png", 0);
	display->loadTextures("nut.png", 1);
	display->loadTextures("brickBackground.png", 2);

	//Hud test
	hud = new Hud;
	hud->CreateElement("hud text test", 0, 0);
	display->draw(hud);
	//end hud

	camera = new Camera(entlist[1]);
	SetDisplayCamera();

	spawn(0);
	randNum();
	spawn(1);
	randNum();
	spawn(2);
	randNum();
	spawn(3);
	randNum();

	Entity *camLock = new Entity();

	// Entity to parent camera. Locking camera to these coordinates
	camLock->x = 0; 
	camLock->y = 100;

	entlist[0]->SetScene(this);

	// Initialize to camera lock entity
	camera->Init(camLock); 

	return success;
}

/*
============================Spawn()============================
Takes an entity ID, spawns the appropriate entity by
instantiating it and placing it in the entlist array, which
is iterated through for updating and displaying in Update().
===============================================================
*/
int BaileyScene::spawn(int entid)
{
	if (entid == 0) // Player
	{

		entlist[entcount] = new BaileyPlayer(&currentTime);
		entlist[entcount]->setListID(entcount);
		entcount++;

		return 0;
	}
	else if (entid == 1) // Enemy
	{

		int randX = randNum();

		entlist[entcount] = new BaileyEnemy(1, this);
		entlist[entcount]->speed = 2;
		entlist[entcount]->acceleration = 1;
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(randX, -330);
		entcount++;

		return 0;
	}
	else if (entid == 2)
	{

		int randX = randNum();

		entlist[entcount] = new BaileyEnemy(2, this);
		entlist[entcount]->speed = 4;
		entlist[entcount]->acceleration = 1;
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(randX, -330);
		entcount++;

		return 0;

	}
	else if (entid == 3)
	{

		int randX = randNum();
		
		randX = randX * 100;

		entlist[entcount] = new BaileyEnemy(3, this);
		entlist[entcount]->speed = 3;
		entlist[entcount]->acceleration = 1;
		entlist[entcount]->setListID(entcount);
		entlist[entcount]->setXY(randX, -330);
		entcount++;

		return 0;

	}
	else { cout << "can't spawn entity" << endl; return 0; }
} //end spawn

/*
============================Despawn()==========================
Calls the destructor on an entity and removes it from the array
of entities in this scene. Sorts the array of entities so that
there are no gaps.
===============================================================
*/
int BaileyScene::despawn(Entity* entity)
{
	if (entcount < 1) { cout << "nothing to despawn" << endl;  return 0; }

	int old = entity->getListID();
	int right = entcount - old;

	if (old < entcount)
	{
		//delete entity;
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

/*
============================LoadMap()==========================
Used by a command to initiate a map loading sequence. If it
is successful, set the map to the next map and end the scene.
When the scene ends, the game will immediately start a new scene
with the new map.
===============================================================
*/
void BaileyScene::LoadMap(std::string t_name)
{
	const char* name = t_name.c_str();
	if (world->CheckExist(name)) {
		printf("Loaded: %s\n", name);
		endcondition = 4; //Start next scene
		game->SetNextMap(t_name); //Load this after this one closes
		done = true;
	}
	else {
		printf("Map '%s' does not exist!\n", name);
	}
}


bool BaileyScene::TimeUp()
{

	return false;

}

unsigned int BaileyScene::GetTime()
{
	return SDL_GetTicks();
}

int BaileyScene::randNum()
{

	int randX = 0;

	srand(time(NULL));

	randX = rand() % 6;

	randX = randX * 100;

	randX = randX - 300;

	return randX;
}

/*
void Scene::SetDisplayCamera()
{
	display->SetCamera(&camera);
}
*/

/*
==========================HandleCommand()======================
Used by elements within the scene to push commands to the game.
Used by the console and by buttons to issue commands to the
current scene or elements in the scene.
===============================================================
*/
void BaileyScene::HandleCommand(Command* command)
{
	cbus.PostCommand(command);
}

/*
==========================SceneLoop()=========================
Control behavior for when the scene is not in "edit" mode.
Meaning we cannot create brushes.
===============================================================
*/
void BaileyScene::SceneLoop() {
	//input->keyEvents();
	if (input->getMouse() != 0)
	{
		//Send to gui before we do camera offset calculations
		gui->CheckMouse(input->mousex, input->mousey);

		entlist[0]->TestQueue(); //test queue functionality
		//cout << "click" << endl;
		mousex = input->mousex + camera->x;
		mousey = input->mousey + camera->y;

		/*
		Entlist spawn testing (turned off)
		*/
		if (input->mousex > 700 && input->mousex < 750 && input->mousey > 500 && input->mousey < 550)
		{
			//never do anything
			if (create)
			{
				create = false;
			}
			else create = true;
		}
		else
		{
			if (create)
			{
				if (mousex > 400)spawn(1);
				else(spawn(2));
			}
		}
	} //end if
}

/*
==========================EditLoop()===========================
If edit mode is on, we can click and drag the mouse to create
new brushes that immediately become usable.
===============================================================
*/
void BaileyScene::EditLoop() 
{
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

/*
==========================Update()=============================
Execute any commands in the command bus, get control states,
update entities, camera, world, and draw them. Get rid of anything
left in the command bus at the end of the frame.
===============================================================
*/
void BaileyScene::Update()
{

	currentTime = SDL_GetTicks(); //update current time

	Execute(); //cbus commands

	//entlist[1]->Move(entlist[1]);

	/*
	Player input commands.
	*/
	if (input->flags & IF_LEFT) {
		entlist[0]->Input(IF_LEFT);
	}
	if (input->flags & IF_RIGHT) {
		entlist[0]->Input(IF_RIGHT);
	}
	if (input->flags & IF_SPACE) {
		entlist[0]->Input(IF_SPACE);
	}
	if (input->flags & IF_CTRL) {
		entlist[0]->Input(IF_CTRL);
	}


	for (int i = 1; i < entcount; i++)
	{

		if (entlist[i]->y > 450)
		{

			despawn(entlist[i]);

			spawn(typecount);
			typecount++;
		}
		else if (entcount < 4) {
			spawn(typecount);
			typecount++;
		}

		if (typecount > 3) {
			typecount = 1;
		}
	}


	/*
	Toggle edit mode on and off.
	*/
	if (input->flags & IF_TAB) {
		EditLoop();
	}
	else {
		SceneLoop();
	}

	entlist[0]->update();
	camera->update();

	//Iterate through all the brushes but stop as soon as we hit one of them and start over.
	entlist[0]->onGround = false; //moved this out of checkbounds for now.
	entlist[0]->collideSide[0] = false;
	entlist[0]->collideSide[1] = false;
	for (int i = 0; i < world->brushCount; i++) {
		collision.checkBounds(entlist[0], world->brushes[i]);
	}


	for (int i = 0; i < entcount; i++) {
		//if (i != 0)movement.move(entlist[i]);

		if (i != 0)collision.checkBounds(entlist[0], entlist[i]);
		if (i != 0) {
			for (int j = 0; j < world->brushCount; j++) {
				collision.checkBounds(entlist[i], world->brushes[j]);
			}
		}
		//if (i != 0 && !create)collision.checkBounds(entlist[i], mousex, mousey);
		if (i != 0)entlist[i]->update(); //if collide, do not update to newX/newY
		if (entlist[i]->getIsDead())despawn(entlist[i]);
	}

	background->Update();
	display->draw(background);
	for (int i = 0; i < entcount; i++) {
		display->draw(entlist[i]);
	}

	display->draw(world); //draw world!

	display->DrawScore(score);

	gui->Update(); //update buttons


	cbus.Tick(); //Clear current command in cbus

	//display->render(); //draw to screen moved to game
}
