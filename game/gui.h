// gui.h
// Alex Rutan
// 11/12/18

#ifndef GUI_EXIST
#define GUI_EXIST

#include <iostream>

class Display;
class Button;
class Scene;
class Menu; //get rid of menu include when inheritance from scene abstract implemented properly.
class Command;
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
		Scene *scene = nullptr;
		Menu *mscene = nullptr;
		//Display* GetGui();
		void Update();
		void SetDisplay(Display* display);
		void SetScene(Scene* scene);
		void SetScene(Menu* scene);
		void CheckMouse(const int x, const int y);
		void SetMessage(const char* message);
		const char* GetMessage();
		void CreateButton(const char* name, const int x, const int y, const int w, const int h, Command* command);
		void DrawButton(Button* button);
		void SendCommand(Command *command);

}; //end Gui

#endif //Gui_EXISTS
