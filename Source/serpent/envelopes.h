////////////////////////////////////////////////////////////////////////////////////////
// ENVELOPES
// V.0.3.6 2022-02-19
////////////////////////////////////////////////////////////////////////////////////////
#pragma once



#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

using std::vector;


namespace cell{
    
typedef struct
{
    float  time;
    float value;
} BREAKPOINT;

typedef struct
{
    BREAKPOINT A;
    BREAKPOINT D;
    BREAKPOINT S;
    BREAKPOINT R;
} ADSR;

class envelope
{
    private:
    public:
        enum   STAGE {OFF, A, D, S, R};
        enum   TYPE  {LIN, LOG, CUB, SFT};
        STAGE  state = OFF;
        ADSR   adsr;
        TYPE   curve = CUB;
        uint   departed;      // Current sample
        uint   breakpoint;    // Samples before next stage
        int    form[4];       // Function for given segment
        float  sample_rate;   // System sample rate
        float  e;             // Multiplier
        float  level;         // Previous - Next
        float  scale;         // Overall time multiplier
        float  min;           // Floor
        float  out;           // Current output
        float  coefficient(float, float, uint);
        float  process();
        void   start();          
        void   next_stage();
        void   init();
        float  iterate();
        envelope();
       ~envelope();
};


float fLinear(float, float, float, float);
float fCubicIn(float, float, float, float);
float fCubicOut(float, float, float, float);
float fCubicIO(float, float, float, float);

inline float (*fCUBe[])(float, float, float, float) = 
                                                    { 
                                                        fLinear,
                                                        fCubicOut,
                                                        fCubicIn,
                                                        fCubicIO
                                                    
                                                    };
float fO(envelope*);
float fAttack(envelope*);
float fDecay(envelope*);
float fSustain(envelope*);
float fRelCUBe(envelope*);

inline float (*fEnv[])(envelope* o) = {fO, fAttack, fDecay, fSustain, fRelCUBe};

vector<float> imprint(envelope*, int, int);

};