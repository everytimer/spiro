#ifndef FORM_FUNCTIONS
#define FORM_FUNCTIONS
#include "cvframe.hpp"
#include "colour_functions.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>

void PSET_SINE(cvframe &canvas, unsigned amplitude, unsigned pitch){
        double Z = 0, Y = 0;
        for (double X= 0; X < canvas.width; X+=(1.0f/pitch)){
                Z=X*M_PI/180*pitch; Y=(sin(Z));
                canvas.pset(X,Y*amplitude+240,0x0);
        }
}

void PSET_CIRCLE(cvframe &canvas, unsigned x, unsigned y, unsigned r){
        for(int i=0; i<360; i++){
                canvas.pset(sin(i)*r+x, cos(i)*r+y,0x0);
        }
}


// draws a pixel on screen of given brightness
void PSET(int x, int y, float brightness, uint colour, cvframe *canvas)
{
        RGBA C = GET_RGBA(colour);
		canvas->pset(x, y, SET_RGBA(C.R*brightness,C.G*brightness,C.B*brightness,C.A*brightness));
}

float fPart(float x)
{
	if (x>0) return x - int(x);
	else return x - (int(x)+1);

}

void WULine(int x0 , int y0 , int x1 , int y1, uint colour, cvframe *canvas)
{
	int steep = abs(y1 - y0) > abs(x1 - x0) ;

	// swap the co-ordinates if slope > 1 or we
	// draw backwards
	if (steep)
	{
		std::swap(x0 , y0);
		std::swap(x1 , y1);
	}
	if (x0 > x1)
	{
		std::swap(x0 , x1);
		std::swap(y0 , y1);
	}

	//compute the slope
	float dx = x1-x0;
	float dy = y1-y0;
	float gradient = dy/dx;
	if (dx == 0.0) gradient = 1;

	int xpxl1 = x0;
	int xpxl2 = x1;
	float intersectY = y0;

	// main loop
	if (steep)
	{
		int x;
		for (x = xpxl1 ; x <=xpxl2 ; x++)
		{
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			PSET((int)(intersectY), x, 1.0f-fPart(intersectY), colour, canvas);
			PSET((int)(intersectY)-1, x,    fPart(intersectY), colour, canvas);
			//std::cout<<fmodf(intersectY,NULL)<<"\n";
			intersectY += gradient;
		}
	}
	else
	{
		int x;
		for (x = xpxl1 ; x <=xpxl2 ; x++)
		{
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			PSET(x, (int)(intersectY), 1.0f-fPart(intersectY), colour, canvas);
			PSET(x, (int)(intersectY)-1,	fPart(intersectY), colour, canvas);
			std::cout<<fPart(intersectY)<<"\n";
			intersectY += gradient;
		}
	}
}


#endif