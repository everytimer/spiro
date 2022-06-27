#pragma once

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "colour_functions.hpp"
#include "curves.hpp"
#include "containers.hpp"
#include <bitset>

namespace cell {


// void Imprint(Frame *canvas, float xo, float yo, const int w, const int h, bool* data, uint colour)
// {
//     for(int y = 0; y < h; y++)
//     {
//         for(int x = 0; x < w; x++)
//         {
//             if(data[x+y*w])
//             {
//                 canvas->pset(x+xo, y+yo, colour);
//             }
//         }
//     }
// }




// void PSetAlpha(Frame *canvas, float x, float y, uint colour) // Alpha point
// {
//     canvas->pset(x, y, ADD(canvas->at(x, y), colour));
// }


///////////////////////////////////////////////////////////////////////////////////////////
// DDA Line ///////////////////////////////////////////////////////////////////////////////
inline void DrawLineDDA(cell::frame<float> *canvas, float xo, float yo, float xe, float ye, float alpha) 
{
    float dx = xe - xo;
    float dy = ye - yo;
    float step;
    if (abs(dx) >= abs(dy)) step = abs(dx);
    else step = abs(dy);
    dx /= step;
    dy /= step;
    float x = xo;
    float y = yo;
    int   i = 1;
    while (i <= step) 
    {
        canvas->set(round(x), round(y), alpha);
        x += dx;
        y += dy;
        i++;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////
// Wu Line ////////////////////////////////////////////////////////////////////////////////
inline void DrawLineW(cell::frame<float>* canvas, float xi, float yi, float xe, float ye, uint alpha) 
{
    
    bool steep = abs(ye - yi) > abs(xe - xi);
    
    if (steep) 
	{
        std::swap(xi, yi);
        std::swap(xe, ye);
	}
    if (xi > xe) 
	{
        std::swap(xi, xe);
        std::swap(yi, ye);
	}
    
    float dx = xe - xi;
    float dy = ye - yi;


    float gradient = 1.0f;
    if (dx != 0.0f) gradient = dy / dx;

    // handle first endpoint
    float tpart;
    float xend = round(xi);
    float yend = yi + gradient * (xend - xi);
    float xgap = 1.0f - modff(xi + 0.5f, &tpart);
    float xpxl1 = xend; // this will be used in the main loop
    float ypxl1 = int(yend);

    if (steep) 
	{
        canvas->set(ypxl1,   xpxl1, alpha*(1.0f - modff(yend, &tpart) * xgap));
        canvas->set(ypxl1 + 1, xpxl1,  alpha* modff(yend, &tpart) * xgap);
	}
    else
	{
        canvas->set(xpxl1, ypxl1  ,  alpha*(1.0f - modff(yend, &tpart) * xgap));
        canvas->set(xpxl1, ypxl1 + 1,  alpha*modff(yend, &tpart) * xgap);
	}
    float intery = yend + gradient; // first y-intersection for the main loop
    
    // handle second endpoint
    xend = round(xe);
    yend = ye + gradient * (xend - xe);
    xgap = modff(xe + 0.5, &tpart);
    float xpxl2 = xend; //this will be used in the main loop
    float ypxl2 = int(yend);

    if (steep)
	{
        canvas->set(ypxl2  , xpxl2,  alpha*(1.0f - modff(yend, &tpart) * xgap));
        canvas->set(ypxl2+1, xpxl2,  alpha*modff(yend, &tpart) * xgap);
	}
	else
	{
        canvas->set(xpxl2, ypxl2,    alpha*(1.0f - modff(yend, &tpart) * xgap));
        canvas->set(xpxl2, ypxl2+1,  alpha*modff(yend, &tpart) * xgap);
	}
    
    // main loop
    if (steep)
	{
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x += 1.0f)
        {
            canvas->set(int(intery)  , x,  alpha*(1 - modff(intery, &tpart)));
            canvas->set(int(intery)+1, x,  alpha*modff(intery, &tpart));
            intery += gradient;
		}
	}
    else
	{
        for (float x = xpxl1 + 1; x <= xpxl2 - 1; x += 1.0f)
        {
            canvas->set(x, int(intery),    alpha*(1 - modff(intery, &tpart)));
            canvas->set(x, int(intery)+1,  alpha*modff(intery, &tpart));
            intery += gradient;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////
// Bresenham //////////////////////////////////////////////////////////////////////////////
inline void DrawLineB(cell::frame<float>* canvas, float xi, float yi, float xe, float ye, float alpha) 
{
    const bool steep = (fabs(ye - yi) > fabs(xe - xi));
    if(steep)
    {
        std::swap(xi, yi);
        std::swap(xe, ye);
    }
    
    if(xi > xe)
    {
        std::swap(xi, xe);
        std::swap(yi, ye);
    }
    
    const float dx = xe - xi;
    const float dy = fabs(ye - yi);
    
    float error = dx / 2.0f;
    const int ystep = (yi < ye) ? 1 : -1;
    int y = (int)yi;
    
    const int maxX = (int)xe;
    
    for(int x=(int)xi; x<=maxX; x++)
    {
        if(steep)
        {
            canvas->set(y, x, alpha);
        }
        else
        {
            canvas->set(x, y, alpha);
        }
    
        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}


// ///////////////////////////////////////////////////////////////////////////////////////////
// // MidPoint Algorhithm ////////////////////////////////////////////////////////////////////
// void DrawCircleM(Frame *canvas, float xo, float yo, float radius, uint colour) 
// {
//     int f = 1 - radius;
//     int ddF_x = 0;
//     int ddF_y = -2 * radius;
//     int x = 0;
//     int y = radius;
 
//     canvas->pset(xo, yo + radius, colour);
//     canvas->pset(xo, yo - radius, colour);
//     canvas->pset(xo + radius, yo, colour);
//     canvas->pset(xo - radius, yo, colour);
 
//     while(x < y) 
//     {
//         if(f >= 0) 
//         {
//             y--;
//             ddF_y += 2;
//             f += ddF_y;
//         }
//         x++;
//         ddF_x += 2;
//         f += ddF_x + 1;    
//         canvas->pset(xo + x, yo + y, colour);
//         canvas->pset(xo - x, yo + y, colour);
//         canvas->pset(xo + x, yo - y, colour);
//         canvas->pset(xo - x, yo - y, colour);
//         canvas->pset(xo + y, yo + x, colour);
//         canvas->pset(xo - y, yo + x, colour);
//         canvas->pset(xo + y, yo - x, colour);
//         canvas->pset(xo - y, yo - x, colour);
//     }
// }
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


// ///////////////////////////////////////////////////////////////////////////////////////////
// // MidPoint Algorhithm ////////////////////////////////////////////////////////////////////
// void DrawRoundedBox(Frame *canvas, int xo, int yo, int width, int height, int radius, uint colour) 
// {
//     int f = 1 - radius;
//     int ddF_x = 0;
//     int ddF_y = -2 * radius;
//     int x = 0;
//     int y = radius;
 
//     while(x < y) 
//     {
//         if(f >= 0) 
//         {
//             y--;
//             ddF_y += 2;
//             f += ddF_y;
//         }
//         x++;
//         ddF_x += 2;
//         f += ddF_x + 1;    
//         // Left upper /////////////////////////////////////////
//         canvas->pset(xo - y + radius, yo - x + radius, colour);
//         canvas->pset(xo - x + radius, yo - y + radius, colour);
//         // Right upper ////////////////////////////////////////////////
//         canvas->pset(xo + x + width - radius, yo - y + radius, colour);
//         canvas->pset(xo + y + width - radius, yo - x + radius, colour);
//         // Left lower //////////////////////////////////////////////////
//         canvas->pset(xo - x + radius, yo + y + height - radius, colour);
//         canvas->pset(xo - y + radius, yo + x + height - radius, colour);
//         // Right lower /////////////////////////////////////////////////////////
//         canvas->pset(xo + x + width - radius, yo + y + height - radius, colour);
//         canvas->pset(xo + y + width - radius, yo + x + height - radius, colour);
         
//     }
//     int xe = xo + width - radius;
//     int ye = yo + height;
//     for(int i = xo + radius; i <= xe; i++)
//     {
//         canvas->pset(i, yo, colour);
//         canvas->pset(i, ye, colour);
//     }
//     xe = xo + width;
//     ye = yo + height - radius;
//     for(int i = yo + radius; i <= ye; i++)
//     {
//         canvas->pset(xo, i, colour);
//         canvas->pset(xe, i, colour);
//     }
// }

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





// void DrawSpline(catmullrom &S, Frame &canvas, const uint colour) 
// {
//         int W = canvas.width;
//         // int H = canvas.heigth;

//         S.calcv();
//         for(int X=0; X<W*2; X++)
//         {
//             Point<double> P =  S.getft(double(X)/300.0);
//             canvas.pset(P.x, P.y, colour);
//         }
// }

// //////////////////////////////////////////////////////////////////////////////
// // Stefan Gustavson (stegu@itn.liu.se) 2003-08-20 ////////////////////////////
// // https://weber.itn.liu.se/~stegu/circle/circlealgorithm.pdf ////////////////
// //////////////////////////////////////////////////////////////////////////////

// void DrawCircleF(Frame *canvas, int xo, int yo, int radius, const uint colour)
// {
//     int x  = 0; 
//     int y  = radius; 
//     int d  = 5 - 4 * radius;
//     int dA = 12; 
//     int dB = 20 - 8 * radius;

//     while (x < y)
//     {
//         canvas->pset( x + xo,  y + yo, colour);
//         canvas->pset( x + xo, -y + yo, colour);
//         canvas->pset(-x + xo,  y + yo, colour);
//         canvas->pset(-x + xo, -y + yo, colour);
//         canvas->pset( y + xo,  x + yo, colour);
//         canvas->pset( y + xo, -x + yo, colour);
//         canvas->pset(-y + xo,  x + yo, colour);
//         canvas->pset(-y + xo, -x + yo, colour);

//         if(d < 0)
//         {
//             d  += dA; 
//             dB += 8;
//         }
//         else
//         {
//             y--;
//             d  += dB; 
//             dB += 16;
//         }
        
//         x++; 
//         dA += 8;
//     }
// }


// ///////////////////////////////////////////////////////////////////////////////////////////
// // MidPoint Algorhithm ////////////////////////////////////////////////////////////////////
// void DrawRoundedBoxFilled(Frame *canvas, int xo, int yo, int width, int height, int radius, uint colour) 
// {
//     int x  = 0; 
//     int y  = radius; 
//     int d  = 5 - 4 * radius;
//     int dA = 12; 
//     int dB = 20 - 8 * radius;

//     while (x <= y)
//     {
  
//         for(int i = xo - y + radius; i<=(xo + y + width - radius); i++) 
//         {
//             canvas->pset(i, yo - x + radius, colour);
//             canvas->pset(i, yo + x + height - radius, colour);
//         }
//         for(int i = xo - x + radius; i<=(xo + x + width - radius); i++) 
//         {
//             canvas->pset(i, yo - y + radius, colour);
//             canvas->pset(i, yo + y + height - radius, colour);
//         }
        
//         if(d < 0)
//         {
//             d  += dA; 
//             dB += 8;
//         }
//         else
//         {
//             y--;
//             d  += dB; 
//             dB += 16;
//         }
        
//         x++; 
//         dA += 8;
//     }
//     DrawRectangleFilled(canvas, xo, yo + radius, width, height - radius*2, colour);
// }


/////////////////////////////////////////////////////////////////////////////////////
// https://github.com/miloyip/line/blob/master/line_sdfaabb.c ///////////////////////
// Signed distnace field (SDF) optimization with AABB ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

inline float capsuleSDF(float px, float py, float ax, float ay, float bx, float by, float r) 
{
    float pax = px - ax; 
    float pay = py - ay;
    float bax = bx - ax;
    float bay = by - ay;
    float h   = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    float dx  = pax - bax * h;
    float dy  = pay - bay * h;
    return sqrtf(dx * dx + dy * dy) - r;
}


inline void DrawLineSDFAABB(cell::frame<float>* canvas, float xo, float yo, float xe, float ye, float r, float alpha) 
{
    int xa = (int)floorf(fminf(xo, xe) - r);
    int xb = (int) ceilf(fmaxf(xo, xe) + r);
    int ya = (int)floorf(fminf(yo, ye) - r);
    int yb = (int) ceilf(fmaxf(yo, ye) + r);
    for (int y = ya; y <= yb; y++)
        for (int x = xa; x <= xb; x++)
            canvas->set(x, y, alpha*(1.0-fmaxf(fminf(0.5f - capsuleSDF(x, y, xo, yo, xe, ye, r), 1.0f), 0.0f)));
}

};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////