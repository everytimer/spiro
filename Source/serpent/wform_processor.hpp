////////////////////////////////////////////////////////////////////////////////////////
// Waveform processor
// V.0.0.1 2022-02-04
////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include "delay.h"
#include "utility.hpp"
#include "reverb.hpp"
//#include "chorus.hpp"

struct waveform_processor
{
    enum    CHANNEL {LEFT, RIGHT};
    int     sources = 3;
    limiter limit;
    reverb  rv[3];
    float*  source[3];
    float*  amount;
    float*  pan[3];
    float   symmetry    = 1.0f;
    float   drive[3];
    float   gain[3];
    float   mix[3];
    int     mode        = 0;
    float   feed;

    waveform_processor();
    ~waveform_processor() {};
};

inline float fDistort(waveform_processor& o, int idx)
{
    return  xfade
            (
                sinf
                (
                    atanf(*o.source[idx] * (o.gain[idx]+0.02f)*50.0f) * (o.drive[idx]*0.5f+1.0f)
                ), 
                   *o.source[idx], 
                    o.mix[idx]
            );
}

inline float fSaturate(waveform_processor& o, int idx)
{
    return  xfade
            (
                sinf
                (
                    tanhf(*o.source[idx] * (o.gain[idx]+0.02f)*20.0f) * (o.drive[idx]*1.5f+1.0f)
                ), 
                   *o.source[idx], 
                    o.mix[idx]
            );
}

inline float fReverb(waveform_processor& o, int idx)
{
    if(o.rv[idx].amount > o.rv[idx].threshold)
    {
        o.rv[idx].init();
        return o.rv[idx].process(*o.source[idx]);
    }
    else return *o.source[idx];
}


inline float (*fFx[])(waveform_processor&, int) = { fSaturate, fDistort, fReverb };
 
inline waveform_processor::waveform_processor()
{
    amount         = nullptr;
    source[0]      = nullptr;
    source[1]      = nullptr;
    source[2]      = nullptr;
}


inline float fMix(waveform_processor* o, const waveform_processor::CHANNEL& c)
{
    for(int i = 0; i < o->sources; i++)
    {
        *o->source[i] = fFx[0](*o, i);
        *o->source[i] = fFx[2](*o, i);
    }

    if(c == waveform_processor::CHANNEL::LEFT)
    {
        o->feed = (*o->source[0]*(1.0f-*o->pan[0]) + *o->source[1]*(1.0f-*o->pan[1]) + *o->source[2]*(1.0f-*o->pan[2]))**o->amount;
    }
    if(c == waveform_processor::CHANNEL::RIGHT)
    {
        o->feed = (*o->source[0]**o->pan[0] + *o->source[1]**o->pan[1] + *o->source[2]**o->pan[2])**o->amount;
    }
    return o->limit.process(o->feed);
}

// Symmetry in range: -1.0:1.0
// Input range      :  0.0:1.0
// Correction       :  Input*2-1
inline float fWProcess(waveform_processor* o, const waveform_processor::CHANNEL& c)
{
    float symmetry = o->symmetry*2.0f-1.0f;
    o->feed = ((*o->source[0] * (symmetry + *o->source[1])) + (*o->source[2] * (symmetry-*o->source[1]))) ** o->amount;
    return o->feed;
}


inline float (*fProcess[])(waveform_processor*, const waveform_processor::CHANNEL&) = {fMix, fWProcess};




