
// ==============================================================================
//   automata.h
//   Created: 13 Jun 2022 1:09:32pm
//   Author:  unmanned
// ==============================================================================


#pragma once
//////////////////////////////////////////////////////////////////////////////////
// Langtons Ant //////////////////////////////////////////////////////////////////
struct langtons_ant
{
        enum direction { UP, RIGHT, DOWN, LEFT };
        direction current = UP;

        bool *field;
        int w, h, l;
        int x, y, pos;

        void move();
        void clr();
        langtons_ant(const int&, const int&);
        langtons_ant();
       ~langtons_ant();
};