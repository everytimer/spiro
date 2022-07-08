////////////////////////////////////////////////////////////////////////////////////////
// ENVELOPES
// V.0.3.7 2022-07-07
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
using std::vector;


namespace cell{
    
struct breakpoint
{
    enum  type  { LIN, LOG, CUB, SFT };
    uint  time  = 0;
    float value = 0.0f;
    type  curve = SFT;
};


class envelope
{
    private:
        float  value = 0.0f;  // Starting value
        float  delta = 0.0f;  // Change in values
        float  floor = 0.0f;
    public:
        breakpoint* node;
        uint   departed;        // Current sample
        float  scale;           // Overall time multiplier
        float  threshold = 0.0f;// Floor
        float  feed;            // Current output
        int    segments = 6;    // Number of stages
        int    stage = 0;       // Current stage
        void   start();          
        void   next_stage();
        void   init();
        float  iterate();
        envelope();
       ~envelope();
};


float fLinear  (float, float, float, float);
float fCubicIn (float, float, float, float);
float fCubicOut(float, float, float, float);
float fCubicIO (float, float, float, float);

inline float (*formEnvelope[])(float, float, float, float) = 
                                                    { 
                                                        fLinear,
                                                        fCubicOut,
                                                        fCubicIn,
                                                        fCubicIO
                                                    };


vector<float> imprint(envelope*, int, int);

};