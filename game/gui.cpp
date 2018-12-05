// gui.cpp
// Alex Rutan
// 11/12/18
#include <iostream>
#include "gui.h"
#include "display.h"
#include "entity.h"
#include "command.h"
#include "console.h"
#include "scene.h"
#include "menu.h"

using namespace std;

const int HOVER = 1;
const int DOWN = 2;

/*
============================Button=============================
Define the class here since no one else can make buttons.
===============================================================
*/
class Button : public Entity{
	private:
		bool active = true;
		const char* name;
		Gui *gui = nullptr;
		Command *command;

	public:
		Button();
		Button(const char* name, const int x, const int y, const int w, const int h, Command *command);
		~Button();
		void SetGui(Gui * gui);
		void update();
		void Hovered(bool hover);
		void Press();
		void Release();

		int state = 0;
};
/*
/*
Gui constructor 
 */
Gui::Gui()
{
} //end constructor

Gui::Gui(Display* t_display)
{
	display = t_display;
} //end constructor

Gui::~Gui()
{
} //end destructor

void Gui::Update()
{
	for (int i = 0; i < buttonAmount; i++) {
		buttons[i]->update();
		DrawButton(buttons[i]);
	}
}

void Gui::SetDisplay(Display * t_display)
{
	display = t_display;
}

void Gui::SetScene(BaseScene * t_scene)
{
	scene = t_scene;
}

/*
void Gui::SetScene(Scene * t_scene)
{
	scene = t_scene;
}
*/

void Gui::SetScene(Menu * t_scene) {
	mscene = t_scene;
}

/*
============================CheckMouse=========================
Check to see if we've clicked on a button.
===============================================================
*/
void Gui::CheckMouse(const int x, const int y)
{
	int leftb = 0;
	int rightb = 0;
	int topb = 0;
	int bottomb = 0;
	/*
	Get the boundaries for each button.
	*/
	for (int i = 0; i < buttonAmount; i++) {
		leftb = buttons[i]->x;
		rightb = leftb + buttons[i]->width;
		topb = buttons[i]->y;
		bottomb = topb + buttons[i]->height;

		/*
		// ================DEBUG================
		if (x > leftb) {
			cout << "left pass" << endl;
			cout << x << endl;
			cout << leftb << endl;
		}

		if (x < rightb) {
			cout << "right pass" << endl;
		}
		if (y > topb) {
			cout << "top pass" << endl;
		}
		if (y < bottomb) {
			cout << "bottom pass" << endl;
		}
		// =====================================
		*/
		if (x > leftb && x < rightb && y > topb && y < bottomb) {
			buttons[i]->state |= HOVER | DOWN;
			cout << "HOVER AND DOWN" << endl;
		}
		else {
			buttons[i]->state &= ~(HOVER);
		}
	}
}

void Gui::SetMessage(const char* t_message)
{
	m_message = t_message;
}

const char* Gui::GetMessage()
{
	return m_message;
}

void Gui::CreateButton(const char * name, const int x, const int y, const int w, const int h, Command* command)
{
	buttons[buttonAmount] = new Button(name, x, y, w, h, command);
	buttons[buttonAmount]->SetGui(this);
	buttonAmount++;
}

void Gui::DrawButton(Button * button)
{
	display->draw(
		button->x,
		button->y,
		button->width,
		button->height
	);
}

/*
============================SendCommand()======================
Send a command to the scene if a button has been clicked.
===============================================================
*/
void Gui::SendCommand(Command * command)
{
	//Temporary until menu is of type scene.
	if (scene != nullptr) {
		scene->HandleCommand(command);
	}
	else {
		mscene->HandleCommand(command);
	}
}

Button::Button()
{
}

/*
============================Button()===========================
Define where the button is and what it does when clicked.
===============================================================
*/
Button::Button(const char * t_name, const int t_x, const int t_y, const int t_w, const int t_h, Command *t_command)
{
	name = t_name;
	x = t_x;
	y = t_y;
	width = t_w;
	height = t_h;
	command = t_command;
}

Button::~Button()
{
}

void Button::SetGui(Gui *t_gui)
{
	gui = t_gui;
}

void Button::update() {
	//printf("State: %d, Hover: %d, Down: %d \n", state, DOWN, HOVER);
	if (state & DOWN && state & HOVER) {
		cout << "pressed in button update" << endl;
		Press();
	}
}

void Button::Hovered(bool t_hovered) 
{

}

/*
============================Press()============================
Mouse down on button. Send command.
===============================================================
*/
void Button::Press()
{
	Alert("button pressed");
	state &= ~(DOWN);
	//jump.Execute();
	//HandleCommand(jump);
	gui->SendCommand(command);
}

/*
============================Release()==========================
Mouse up on button.
===============================================================
*/
void Button::Release()
{
	if (state & HOVER & DOWN) {
		const char* message = "button pressed";
		Alert(message);
	}
	else {
		state &= ~(DOWN);
	}
}
