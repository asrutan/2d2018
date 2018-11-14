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

using namespace std;

const int HOVER = 1;
const int DOWN = 2;

class Button : public Entity{
	private:
		bool active = true;
		const char* name;
		Gui *gui = nullptr;

	public:
		Button();
		Button(const char* name, const int x, const int y, const int w, const int h);
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

void Gui::SetScene(Scene * t_scene)
{
	scene = t_scene;
}

void Gui::CheckMouse(const int x, const int y)
{
	int leftb = 0;
	int rightb = 0;
	int topb = 0;
	int bottomb = 0;

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

void Gui::CreateButton(const char * name, const int x, const int y, const int w, const int h)
{
	buttons[buttonAmount] = new Button(name, x, y, w, h);
	buttons[buttonAmount]->SetGui(this);
	buttonAmount++;
}

void Gui::DrawButton(Button * button)
{
	display->draw(
		button->x,
		button->y,
		button->height,
		button->width
	);
}

void Gui::SendCommand(Command * command)
{
	scene->HandleCommand(command);
}

Button::Button()
{
}

Button::Button(const char * t_name, const int t_x, const int t_y, const int t_w, const int t_h)
{
	name = t_name;
	x = t_x;
	y = t_y;
	width = t_w;
	height = t_h;
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

void Button::Press()
{
	cout << "button pressed" << endl;
	Alert("button pressed");
	state &= ~(DOWN);
	//jump.Execute();
	//HandleCommand(jump);
	gui->SendCommand(&jump);
}

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
