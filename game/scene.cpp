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

/*
Scene constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Scene::Scene()
{
	Entity *entlist = new Entity[255];
	//entlist = new Entity[255];
	entcount = 0;
    //cout << "Scene constructed" << endl;

	//quit = false;

	//quit = input->GetQuitPtr();
	//editMode = input->GetEditTogglePtr();
	//mouseDown = input->GetMouseDownPtr();

} //end constructor

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
	delete camera;
	camera = nullptr;
	delete[] *entlist;
} //end destructor

Entity & Scene::GetPlayer()
{
	return *entlist[0];
}

int Scene::GetCamX()
{
	return camera->x;
}

int Scene::GetCamY()
{
	return camera->y;
}

bool Scene::loadTextures()
{  
    return true;
} //end loadTextures

bool Scene::Init()
{
	bool success = true;
	printf("Run number: %d \n", game->sceneruntimes);

	world = new World;
	world->define();
	world->Load();
	
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
	int nextScene = 0;

	return success;
}

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

void Scene::HandleCommand(Command* command)
{
	cbus.PostCommand(command);
}

void Scene::Act(int request)
{
	if (request == 1) {
		spawn(3);
	}
}

void Scene::SceneLoop() {
	//input->keyEvents();
	if (input->getMouse() != 0)
	{
		//Send to gui before we do camera offset calculations
		gui->CheckMouse(input->mousex, input->mousey);

		entlist[0]->TestQueue();
		//cout << "click" << endl;
		mousex = input->mousex + camera->x;
		mousey = input->mousey + camera->y;

		if (input->mousex > 700 && input->mousex < 750 && input->mousey > 500 && input->mousey < 550)
		{
			if (create)
			{
				create = false;
			}
			else create = true;
			//entlist[0]->kill();
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
First, take each of the textures and assign them to their own specific rectangles to be drawn later
Create and instance of map, map is loaded when it is constructed
Pass the map information on to player and the setEnemyMap via pointer
Create an instance of camera and send it values for number of rays and player's initial position
Create an instance of SDL_Event for player input, events change bools to "true"
 */

int Scene::End()
{
	printf("\nNEXTSCENE: %d \n", nextScene);
	world->SaveToFile();
	return (nextScene);
}
//end run


void Scene::Update()
{
	currentTime = SDL_GetTicks();

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

	if (input->flags & IF_TAB) {
		SceneLoop();
	}
	else {
		EditLoop();
	}

	entlist[0]->update();
	camera->update();
	/**************/
	//movement.move(entlist[0]); //move, checkbounds, update

	//skeleton
	//collision.checkBounds(entlist[0], world->horizonts[0]);

	//Iterate through all the brushes but stop as soon as we hit one of them and start over.
	for (int i = 0; i < world->brushCount; i++) {
		collision.checkBounds(entlist[0], world->brushes[i]);
		if (entlist[0]->onGround) {
			//cout << i << endl;
			//printf("Brush hit: %d\n", i);
			i = world->brushCount;
		}
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

	display->draw(world);

	gui->Update();

	cbus.Tick();

	//display->render(); //draw to screen

					   // end updates
}
void Scene::SetDone(bool t_done)
{
	done = t_done;
}
//end run

/*
void Scene::SetDisplayCamera() { 
	display->SetCamera(camera); 
}
*/
