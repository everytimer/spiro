////////////////////////////////////////////////////////////////////////////////////////
// Filters
// V.0.1.1 2022-01-30
////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "iospecs.hpp"
#include "constants.hpp"
#include <cmath>


namespace cell {

struct vcf
{
    iospecs*    io;
    float   eax[4];
    float   ebx[4];
    float   ecx[4];
    float   feed;

    float   cutoff  = 1.0f;
    float   drive   = 1.1f;
    float   Q       = 0.0f;

    void    reset();
    vcf();
   ~vcf();
};

inline void vcf::reset()
{
    for(int i = 0; i < 4; i++)
    {
        eax[i] = 0.0f;
        ebx[i] = 0.0f;
        ecx[i] = 0.0f;
    }
}

inline vcf::vcf()                 
{
    reset();
}

inline vcf::~vcf()
{
}

// This model is based on a reference implementation of an algorithm developed by
// Stefano D'Angelo and Vesa Valimaki, presented in a paper published at ICASSP in 2013.
// This improved model is based on a circuit analysis and compared against a reference
// Ngspice simulation. In the paper, it is noted that this particular model is
// more accurate in preserving the self-oscillating nature of the real filter.
// References: "An Improved Virtual Analog Model of the Moog Ladder Filter"
// Original Implementation: D'Angelo, Valimaki

inline float fImprovedLP24(vcf* o, const float& input) 
{
        float aax, abx, acx, adx;
        static const float VT = 0.312f;
        static float g, cutoff;
        if(cutoff!=o->cutoff)
        {
                float f = o->cutoff * 9928.56f + 27.5f;
                float x = (M_PI * f) / o->io->sample_rate;
                g = 4.0 * M_PI * VT * f * (1.0 - x) / (1.0 + x);
                cutoff  = o->cutoff;
        }

        aax = -g * (tanh((o->drive * input + o->Q * 4.0f * o->eax[3]) / (2.0 * VT)) + o->ecx[0]);
        o->eax[0] += (aax + o->ebx[0]) / (2.0 * o->io->sample_rate);
        o->ebx[0] = aax;
        o->ecx[0] = tanh(o->eax[0] / (2.0 * VT));
            
        abx = g * (o->ecx[0] - o->ecx[1]);
        o->eax[1] += (abx + o->ebx[1]) / (2.0 * o->io->sample_rate);
        o->ebx[1] = abx;
        o->ecx[1] = tanh(o->eax[1] / (2.0 * VT));
            
        acx = g * (o->ecx[1] - o->ecx[2]);
        o->eax[2] += (acx + o->ebx[2]) / (2.0 * o->io->sample_rate);
        o->ebx[2] = acx;
        o->ecx[2] = tanh(o->eax[2] / (2.0 * VT));
            
        adx = g * (o->ecx[2] - o->ecx[3]);
        o->eax[3] += (adx + o->ebx[3]) / (2.0 * o->io->sample_rate);
        o->ebx[3] = adx;
        o->ecx[3] = tanh(o->eax[3] / (2.0 * VT));
            
        return o->eax[3];      
}

// Moog VCF
// Author or source: CSound source code, Stilson/Smith CCRMA paper.
// Type: 24db resonant lowpass
// https://www.musicdsp.org/en/latest/Filters/24-moog-vcf.html

inline float fStilsonSmithLP24(vcf* o, const float& input) 
{
    static float cutoff, Q, p, k, r;
    if((cutoff != o->cutoff) || (Q != o->Q))
    {
        float f = (cutoff + cutoff) / o->io->sample_rate; //[0 - 1]
        p = f * (1.8f - 0.8f * f);
        k = p + p - 1.0f;
        // k = 2.0f * sin(f * PI / 2.0f) - 1.0f;
        float t = (1.0f - p) * 1.386249f;
        float v = 12.0f + t * t;
        r = o->Q * (v + 6.0f * t) / (v - 6.0f * t);
        cutoff  = o->cutoff;
        Q       = o->Q;
    }
    //--Inverted feed back for corner peaking
    float x = input - r * o->eax[3];
    //Four cascaded onepole filters (bilinear transform)
    o->eax[0] = x * p + o->ebx[0] * p - k * o->eax[0];
    o->eax[1] = o->eax[0] * p + o->ebx[1] * p - k * o->eax[1];
    o->eax[2] = o->eax[1] * p + o->ebx[2] * p - k * o->eax[2];
    o->eax[3] = o->eax[2] * p + o->ebx[3] * p - k * o->eax[3];
    //Clipper band limited sigmoid
    o->eax[3] = o->eax[3] - (o->eax[3]*o->eax[3]*o->eax[3])/6.0f;
    o->ebx[0] = x;
    o->ebx[1] = o->eax[0];
    o->ebx[2] = o->eax[1];
    o->ebx[3] = o->eax[2];

    return o->eax[3];
}


inline float fPeak(vcf* o, const float& input) 
{
        float r = o->Q * 0.99609375f;
        float f = (1.0f - o->cutoff);
        o->ebx[0] = (1.0f - r) * sqrt(r * (r - 4.0f * (f * f) + 2) + 1);
        o->ebx[1] = 2.0f * f * r;
        o->ebx[2] = -(r * r);
        o->eax[0] = o->ebx[0] * input + o->ebx[1] * o->eax[1] + o->ebx[2] * o->eax[2] + 1.0e-24;
        o->eax[2] = o->eax[1];
        o->eax[1] = o->eax[0];
        return o->eax[0]; 
}





inline float fHighPass(vcf *o, const float& input)
{
        // return (input - o->lp24(input))*0.5f;
}

inline float fBandPass(vcf *o, const float& input)
{
        // return o->peak(input);
}

inline float fNotch(vcf *o, const float& input)
{       
        // return input-o->peak(input);
}

inline float fBypass(vcf *o, const float& input)
{
        // return input;
}

inline float (*filter[])(vcf*, const float&) = 
{ 
        fBypass,                // 0
        fImprovedLP24,          // 1
        fStilsonSmithLP24,      // 2
        fHighPass,              // 3
        fPeak,                  // 4
        fNotch                  // 5
};


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


};
