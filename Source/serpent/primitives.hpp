#pragma once

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "colour_functions.hpp"
#include "curves.hpp"
#include "containers.hpp"
#include <bitset>
#include <iostream>


namespace cell {


template <typename T>
inline void drawRectangleFilled(cell::frame<T>* canvas, int xi, int yi, int width, int height, const T data)
{
    int xe = xi + width;
    int ye = yi + height;

    for(int y = yi; y <= ye; y++)
    {
        for(int x = xi; x <= xe; x++)
        {
            canvas->set(x, y, data);
        }
    }
}

template <typename T>
inline void drawSquareFilled(cell::frame<T>* canvas, square<T> sq, const T data)
{
    int xe = sq.xCentre + sq.radius;
    int ye = sq.yCentre + sq.radius;
    int xo = sq.xCentre - sq.radius;
    int yo = sq.yCentre - sq.radius;

    for(int y = yo; y <= ye; y++)
    {
        for(int x = xo; x <= xe; x++)
        {
            canvas->set(x, y, data);
        }
    }
}

inline void drawRectangle(cell::frame<float>* canvas, int xo, int yo, int width, int height, const float alpha)
{
    int xe = xo + width;
    int ye = yo + height;
    
    for(int i = xo; i <= xe; i++)
    {
        canvas->set(i, yo, alpha);
        canvas->set(i, ye, alpha);
    }
    for(int i = yo; i <= ye; i++)
    {
        canvas->set(xo, i, alpha);
        canvas->set(xe, i, alpha);
    }
}

inline void drawLineV(cell::frame<float>* canvas, int xo, int yo, int ye, const float alpha)
{
    for(int i = yo; i <= ye; i++)
    {
        canvas->set(xo, i, alpha);
    }
}

inline void drawLineH(cell::frame<float>* canvas, int xo, int yo, int xe, const float alpha)
{
    for(int i = xo; i <= xe; i++)
    {
        canvas->set(i, yo, alpha);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////