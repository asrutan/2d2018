// hud.h
// Alex Rutan
// 11/16/15

#ifndef HUD_EXIST
#define HUD_EXIST

using namespace std;
class Hud
{
    private:
		const int TEST = 0;
		void utility();
		struct Element {
			string text = "text";
			int x = 0;
			int y = 0;
		};

    public:
        Hud();
        ~Hud();
		double * stuff;
		void init(double*);
		void disp();
		Element elements[1];
		void CreateElement(string t_text, int t_x, int t_y);
		void UpdateElement(int t_element);
		string GetElementString(int t_element);
		int GetElementX(int t_element);
		int GetElementY(int t_element);

}; //end Hud

#endif //HUD_EXISTS
