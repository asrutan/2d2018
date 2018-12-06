// scene.cpp
// Alex Rutan
// 11/10/18
#include <iostream>
#include "scene.h"
#include "player.h"
#include "game.h"
#include "console.h"
#include "hud.h"

using namespace std;

Scene::Scene()
{
	Entity *entlist = new Entity[255];
	entcount = 0;
} //end constructor

/*
============================Scene()============================
Scene constructor that takes a pointer to the game that
instantiated it.
Gets pointers to:
Game, Input, Display, Gui, Background.
Initializes list of entites.
===============================================================
*/
Scene::Scene(Game *t_game)
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
	editMode = input->GetEditTogglePtr();
	mouseDown = input->GetMouseDownPtr();

} //end constructor

Scene::~Scene()
{
	if (jumpbutton) {
		gui->DeleteJumpButton();
	}
	delete camera;
	camera = nullptr;
	delete[] *entlist;
} //end destructor

Entity & Scene::GetPlayer()
{
	return *entlist[0]; //player is always at first spot in list
}

//Moved to display
bool Scene::loadTextures()
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
bool Scene::Init()
{
	bool success = true;
	printf("Run number: %d \n", game->sceneruntimes);

	gui->CreateButton("jump", 500, 10, 60, 60, &jump);
	jumpbutton = true;

	world = new World;
	world->define();
	world->lines = true;
	world->Load(game->GetNextMap());
	
	//Load background based on world info
	background->SetScene(this);

	display->loadTextures("redDude.png", 0);
	display->loadTextures("blocks.bmp", 1);
	display->loadTextures("greenBackground.bmp", 2);

	//Hud test
	hud = new Hud;
	hud->CreateElement("hud text test", 0, 0);
	display->draw(hud);
	//end hud

	camera = new Camera();
	//display->SetCamera(camera);
	SetDisplayCamera();

	spawn(0);

	entlist[0]->SetScene(this);

	//Create scale enemy demo and rotate enemy demo
	spawn(4);
	spawn(5);

	camera->Init(entlist[0]);

	return success;
}

/*
============================Spawn()============================
Takes an entity ID, spawns the appropriate entity by
instantiating it and placing it in the entlist array, which
is iterated through for updating and displaying in Update().
===============================================================
*/
int Scene::spawn(int entid)
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

/*
============================Despawn()==========================
Calls the destructor on an entity and removes it from the array
of entities in this scene. Sorts the array of entities so that
there are no gaps. 
===============================================================
*/
int Scene::despawn(Entity* entity)
{
	if (entcount < 1) { cout << "nothing to despawn" << endl;  return 0; }

	int old = entity->getListID();
	int right = entcount - old;

	if (old < entcount)
	{
		delete entity;
		entity = NULL;
		for (int i = old; i < entcount-1; i++)
		{
			entlist[i] = entlist[i+1];
			entlist[i]->setListID(i);
		}
		entcount--;
		return 0;
	}
	else if(entity->getListID() == entcount)
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
void Scene::LoadMap(std::string t_name)
{
	const char* name = t_name.c_str();
	if (world->CheckExist(name)) {
		printf("Loaded: %s\n", name);
		endcondition = 1; //Start next scene
		game->SetNextMap(t_name); //Load this after this one closes
		done = true;
	}
	else {
		printf("Map '%s' does not exist!\n", name);
	}
}


bool Scene::TimeUp()
{
	//if()
	return false;
}

unsigned int Scene::GetTime()
{
	return SDL_GetTicks();
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
void Scene::HandleCommand(Command* command)
{
	cbus.PostCommand(command);
}

/*
==========================SceneLoop()=========================
Control behavior for when the scene is not in "edit" mode.
Meaning we cannot create brushes.
===============================================================
*/
void Scene::SceneLoop() {
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
void Scene::EditLoop() {
	//input->keyEvents();
	mousex = input->mousex + camera->x;
	mousey = input->mousey + camera->y;
	if (input->getMouse() != 0){
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
void Scene::Update()
{
	currentTime = SDL_GetTicks(); //update current time

	Execute(); //cbus commands

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
	/**************/
	//movement.move(entlist[0]); //move, checkbounds, update

	//skeleton
	//collision.checkBounds(entlist[0], world->horizonts[0]);

	//Iterate through all the brushes but stop as soon as we hit one of them and start over.
	entlist[0]->onGround = false; //moved this out of checkbounds for now.
	entlist[0]->collideSide[0] = false;
	entlist[0]->collideSide[1] = false;
	for (int i = 0; i < world->brushCount; i++) {
		collision.checkBounds(entlist[0], world->brushes[i]);
		//if (entlist[0]->onGround) {
			//cout << i << endl;
			//printf("Brush hit: %d\n", i);
		//	i = world->brushCount;
		//}
	}

	//collision.checkBounds(entlist[0], world->verts[0]);
	//collision.checkBounds(entlist[0], world->verts[1]);

	//skeleton
	//Act(entlist[0]->SceneRequest());
	//display->update(); // background and clear
	for (int i = 0; i < entcount; i++) {
		if (i != 0)movement.move(entlist[i]);
		collision.checkBounds(entlist[i], world->verts[0]);
		collision.checkBounds(entlist[i], world->verts[1]);
		if (i != 0)collision.checkBounds(entlist[0], entlist[i]);
		if (i != 0 && !create)collision.checkBounds(entlist[i], mousex, mousey);
		if (i != 0)entlist[i]->update(); //if collide, do not update to newX/newY
		if (entlist[i]->getIsDead())despawn(entlist[i]);
	} //update entities
	  /**************/
	background->Update();
	display->draw(background);
	for (int i = 0; i < entcount; i++) {
		display->draw(entlist[i]);
	}

	display->draw(world); //draw world!

	gui->Update(); //update buttons

	cbus.Tick(); //Clear current command in cbus

	//display->render(); //draw to screen moved to game
}
