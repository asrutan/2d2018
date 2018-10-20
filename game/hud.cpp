// hud.cpp
// Alex Rutan
// 11/16/15
#include <iostream>
#include "hud.h"

using namespace std;

Hud::Hud()
{
    stuff;
} //end constructor

Hud::~Hud()
{
} //end destructor

void Hud::utility()
{
    cout << *stuff << endl;
} //end utility

void Hud::init(double *info)
{
    stuff = info;
    utility();
}

void Hud::disp()
{
    cout << *stuff << endl;
}
 //end run
