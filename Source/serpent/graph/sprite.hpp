////////////////////////////////////////////////////////////////////////////////////////
// Circular Sprite looper
// V.0.0.1 5-1-2022
////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <utility>
#include "cvstream.hpp"
#include "frame.hpp"
#include "common.hpp"
using std::pair;


class Sprite
{
    private:
        uint        width;
        uint        height;
        cvstream*   buffer;

    public:
        inline void load        (Frame*, int);
        inline void load        (Frame*);
        inline void render      (Frame*, uint, uint);
        inline void render      (Frame*, uint, uint, int);
        inline void render      (Frame*, uint, uint, char); 

        Sprite                (int, int, int);
       ~Sprite                (void);
};

// Private /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


// Public //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


inline void Sprite::load(Frame* canvas, int position)
{
        buffer->set(canvas->ref(),position);
}

inline void Sprite::load(Frame* canvas)
{
        buffer->set(canvas->ref());
        buffer->next();
}

inline void Sprite::render(Frame* canvas, uint x, uint y)
{
        for(uint Y= 0; Y<height; Y++){
        for(uint X= 0; X<width ; X++){
                canvas->pset(X+x, Y+y, buffer->at()[X+Y*width]);
            }
        }
        buffer->next();
}

inline void Sprite::render(Frame* canvas, uint x, uint y, int position)
{
        for(uint Y= 0; Y<height; Y++){
        for(uint X= 0; X<width ; X++){
                canvas->pset(X+x, Y+y, buffer->at(position)[X+Y*width]);
            }
        }
        buffer->next();
}

// Renders with alpha on using additional alpha coofecient as argument
inline void Sprite::render(Frame* canvas, uint x, uint y, char alpha)
{
        uint src, dst, sr, sg, sb, sa, dr, dg, db, c;

        for(uint Y= 0; Y<height; Y++){
        for(uint X= 0; X<width ; X++){
                
                src =   buffer->at()[X+Y*width];    //foreground
                dst =   canvas->at(X+x, Y+y);       //background

                sr = src & mask_r; sr>>=24;
                sg = src & mask_g; sg>>=16;
                sb = src & mask_b; sb>>=8;
                sa = src & mask_a;

                dr = dst & mask_r; dr>>=24;
                dg = dst & mask_g; dg>>=16;
                db = dst & mask_b; db>>=8;

                dr += (sa * (sr - dr))/255;
                dg += (sa * (sg - dg))/255;
                db += (sa * (sb - db))/255;
                
                c =dr;  c<<=8;   
                c+=dg;  c<<=8;
                c+=db;  c<<=8;

            canvas->pset(X+x, Y+y, c);
        }}
        buffer->next(); 
}



Sprite::Sprite(int w, int h, int nframes)
{
        width = w;
        height= h;
        buffer= new cvstream(width * height, nframes);
}

Sprite::~Sprite()
{
        delete buffer;
}

////////////////////////////////////////////////////////////////////////////////////////