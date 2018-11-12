// gui.h
// Alex Rutan
// 11/12/18

#ifndef GUI_EXIST
#define GUI_EXIST

#include <iostream>

class Display;
class Button;
class Gui
{
	private:
		Display *display = nullptr;
		const char* m_message;
		int buttonAmount = 0;
		Button* buttons[255];

	public:
		Gui();
		Gui(Display* display);
		~Gui();
		//Display* GetGui();
		void Update();
		void SetDisplay(Display* display);
		void CheckMouse(const int x, const int y);
		void SetMessage(const char* message);
		const char* GetMessage();
		void CreateButton(const char* name, const int x, const int y, const int w, const int h);
		void DrawButton(Button* button);

}; //end Gui

#endif //Gui_EXISTS
