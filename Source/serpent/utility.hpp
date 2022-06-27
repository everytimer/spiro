//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
// V.0.3.7 2022-06-15
// MIT License
// Copyright (c) 2022 unmanned
// Envelope follower & Limiter based on: 
// https://www.musicdsp.org/en/latest/Filters/265-output-limiter-using-envelope-follower-in-c.html
// One Pole Low-Pass filter Based on code of: Joel de Guzman. https://github.com/djowel 
// HP Based on code by Patrice Tarrabia https://www.musicdsp.org/en/latest/Filters/38-lp-and-hp-filter.html
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>
#include "constants.hpp"

namespace cell {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DC Block filter ///////////////////////////////////////////////////////////////////////////////////////////////
struct dcb 
{
    float f = 0.995;
    float eax = 0.0f, ebx = 0.0f;
    inline float process(const float& in)
    {
        ebx = in - eax + f * ebx;
        eax = in;
        return ebx;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// One pole LP parameter smooth filter ///////////////////////////////////////////////////////////////////////////
struct onepole 
{
    private:
        float a;
        float b;
        float z;

    public:
        inline onepole(float time, float sample_rate)
        {
            a = expf(-TAO / (time * 0.001f * sample_rate));
            b = 1.0f - a;
            z = 0.0f;
        }
        inline onepole()
        {
            a = expf(-TAO / (1 * 0.001f * 48000));
            b = 1.0f - a;
            z = 0.0f;
        }
        inline float process(float in)
        {
            z = (in * b) + (z * a);
            return z;
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Q: 1.4142 to ~ 0.1  Cutoff: 0.0 - 1.0 /////////////////////////////////////////////////////////////////////////
struct hp 
{
    private:
        float eax = 0.0f;
        float ebx = 0.0f;
    public:
        float cutoff = 0.7f;
        float Q      = 1.4f;


    inline float process(float in)
    {
        float c = (cutoff + Q) * cutoff;
        float out = ((1.0/(1.0+c))*eax+in-ebx)*(1.0-c);
        eax = out;
        ebx = in;
        return out;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct envelope_follower
{
    float a;
    float r;
    float envelope = 0.0f;

    inline void init(float, float, float);
    inline void process(const float& in);
};

inline void envelope_follower::init( float aMs, float rMs, float sample_rate )
{
    a = pow( 0.01, 1.0 / ( aMs * sample_rate * 0.001 ) );
    r = pow( 0.01, 1.0 / ( rMs * sample_rate * 0.001 ) );
}

inline void envelope_follower::process(const float& in)
{
    float f = fabs(in);
    if (f > envelope) envelope = a * ( envelope - f ) + f;
    else              envelope = r * ( envelope - f ) + f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct limiter
{
    envelope_follower e;
    float threshold = 0.1f;
    inline void  init(float, float , float);
    inline float process(const float& in);
    inline limiter();
};

inline limiter::limiter()
{
    init(1.0f, 10.0f, 48000.0f);
}

inline void limiter::init(float aMs, float rMs, float sample_rate)
{
    e.init(aMs, rMs, sample_rate);
}


inline float limiter::process(const float& in)
{
    float out = in;
    e.process(out);
    if(e.envelope>threshold)
    {
        out /= expf(e.envelope - threshold);
    }
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct allpass
{
    float y = 0.0f;
    float a = 0.0f;
    inline float process(float in)
    {
        float out = y + a * in;
        y = in - a * out;
        return out;
    }    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct sample_n_hold
{
    int t = 0;
    float value = 0;

    inline float process(const float& input, const int& time)
    {
        if (t>time)
        {
            t = 0;
            value = input;
        }
        t++;
        return value;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Crossfader: f == 1? a = max; f==0? b = max ////////////////////////////////////////////////////////////////////
inline float xfade(const float& a, const float& b, const float& f)
{
    return a*f + b*(1.0f - f);
}

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////