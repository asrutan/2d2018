//collideBox.h
//PA
//12/6/15

#ifndef COLLIDEBOX_EXIST
#define COLLIDEBOX_EXIST

class collideBox
{
  private:
    int x1;
    int x2;
    int y1;
    int y2;

  public:
    collideBox();
    collideBox(int,int,int,int);
    int getX1();
    int getX2();
    int getY1();
    int getY2();
    void update(int,int,int,int);
    bool contains(collideBox);
};

#endif
