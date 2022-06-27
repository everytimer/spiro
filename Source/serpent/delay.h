////////////////////////////////////////////////////////////////////////////////////////
// Delay
// V.0.0.1 2022-02-04
////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "containers.hpp"
#include "utility.hpp"
#include "filters.hpp"
#include "iospecs.hpp"

namespace cell {

class delay
{
    public:
        float*      data;
        const int   length   = 65536;
        float       tmax     = length/2;
        int         sample   = 0;    // Sample DD->sample
        float       feedback = 0.5f; // 0.0f is endless; 1.0f is one tick
        float       amount   = 0.5f;
        float*      time;
        float*      tone;
        float       eax      = 0.0f;
        float       ebx      = 0.0f;
        int         type;

        int         iPtr,  oPtr;
        float       alpha, beta;
        float       feed;

        void clr();
        delay();
        delay(const int&);
       ~delay();
};

float fDelay (delay*, const float&);
float fFDelay(delay*, const float&);
float fSDelay(delay*, const float&);
float fADelay(delay*, const float&);
float fLDelay(delay*, const float&);
float fNDelay(delay*, const float&);

inline float (*fDD[])(delay*, const float&) = 
{
    fDelay,  // 0
    fFDelay, // 1
    fSDelay, // 2
    fADelay, // 3
    fLDelay, // 4
    fNDelay  // 5   
};


};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



