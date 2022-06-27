// ==============================================================================
//   automata.cpp
//   Created: 13 Jun 2022 1:09:32pm
//   Author:  unmanned
// ==============================================================================

#include "automata.h"

void langtons_ant::move()
{
    if(x > w) x = 0;
    if(y > h) y = 0;
    if(x < 0) x = w;
    if(y < 0) y = h;

    pos = x + w * y;

    if (field[pos] == true)
    {
        field[pos] = false;
        if(current == UP) // Up
        { x++; current = RIGHT; }
        else if(current == RIGHT) // Right
        { y++; current = DOWN; }
        else if(current == DOWN) // Down
        { x--; current = LEFT; }
        else if(current == LEFT) // Left
        { y--; current = UP; }            
    }

    else
    {
        field[pos] = true;
        if(current == UP) // Up
        { x--; current = LEFT; }
        else if(current == RIGHT) // Right
        { y--; current = UP; }
        else if(current == DOWN) // Down
        { x++; current = RIGHT; }
        else if(current == LEFT) // Left
        { y++; current = DOWN; }        
    }
}

langtons_ant::langtons_ant(const int& width, const int& height): w(width), h(height), x(0), y(0)
{
    l = w * h;
    field = new bool[l];
    clr();
}

langtons_ant::langtons_ant(): w(8), h(4), x(0), y(0)
{
    l = w * h;
    field = new bool[l];
    clr();
}

langtons_ant::~langtons_ant()
{
    delete field;
}

void langtons_ant::clr()
{
    for(int i = 0; i < l; i++) field[i] = false;
}

