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

void Hud::CreateElement(string t_text, int t_x, int t_y)
{
	elements[0].text = t_text;
	elements[0].x = t_x;
	elements[0].y = t_y;
}

void Hud::UpdateElement(int t_element)
{

}

string Hud::GetElementString(int t_element)
{
	return elements[t_element].text;
}

int Hud::GetElementX(int t_element)
{
	return elements[t_element].x;
}

int Hud::GetElementY(int t_element)
{
	return elements[t_element].y;
}
 //end run
