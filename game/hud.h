// hud.h
// Alex Rutan
// 11/16/15

#ifndef HUD_EXIST
#define HUD_EXIST

class Hud
{
    private:
       void utility();

    public:
        Hud();
        ~Hud();
	double * stuff;
	void init(double*);
	void disp();

}; //end Hud

#endif //HUD_EXISTS
