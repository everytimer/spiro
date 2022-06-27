////////////////////////////////////////////////////////////////////////////////////////
// Frame - GENERIC GRAPHICS BUFFER
// v.0.0.3  06-01-2022
////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////

class Frame
{
    private:
        uint*           canvas;
    public:   
        const   uint    width;
        const   uint    heigth;             
        inline  void    pset        (uint, uint, uint); // Draw point
        inline  uint    at          (uint, uint) const; // Colour at given point
        inline  uint*   ref() const { return canvas; }  // Returns buffer
        inline  void    clr         (uint);             // Clear screen with defined colour
        Frame(uint, uint);
       ~Frame();
};

    inline void Frame::pset(uint x, uint y, uint colour)
    {
        if(((x>=0)&&(x<width))&&((y>=0)&&(y<heigth)))
        canvas[x+y*width] = colour;
    }

    inline uint Frame::at(uint x, uint y) const
    {
        return canvas[x+y* width];
    }

    inline void Frame::clr(uint c)
    {
        for(uint i=0; i<(heigth*width); ++i) canvas[i]= c;
    }


    Frame::Frame(uint x= 1, uint y= 1): width(x), heigth(y)
    {
        canvas= new uint[heigth*width];
    }

    Frame::~Frame()
    {
        delete canvas;
    }


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////