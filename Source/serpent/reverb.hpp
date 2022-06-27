#pragma once
#include <cmath>
#include "utility.hpp"
#include "chaos.hpp"
#include "delay.h"

#define W 4

struct reverb
{
        delay   d[W];
        allpass f[W];
        limiter limit;
        helmholz hh;
        float   scale       = 0.1f;             // Time scale factor
        float   phi         = 2.0f / (W*W);     // Allpass filter angle increment
        float   theta       =-1.0f;             // Allpass filter angle
        float   amount      = 0.5f;
        float   threshold   = 0.01f;            // Minimum processed amount level
        float   feedback    = 0.8f;
        float   tone        = 1.0f;
        float   e           = 1.0f / sqrtf(W);  // Amplitude scale factor
        float   u           = 1.0f;             // Feedback mix
        float   feed[W];
        float   T[W];
        float   H[W][W][W] =  {{{ 1.0f, 1.0f, 1.0f, 1.0f},
                                { 1.0f,-1.0f, 1.0f,-1.0f},
                                { 1.0f, 1.0f,-1.0f,-1.0f},
                                { 1.0f,-1.0f,-1.0f, 1.0f}},

                               {{ 1.0f, 1.0f,-1.0f, 1.0f},
                                {-1.0f,-1.0f, 1.0f, 1.0f},
                                {-1.0f, 1.0f,-1.0f, 1.0f},
                                { 1.0f, 1.0f, 1.0f, 1.0f}},

                               {{ 1.0f, 1.0f, 1.0f, 1.0f},
                                {-1.0f, 1.0f,-1.0f, 1.0f},
                                {-1.0f,-1.0f, 1.0f, 1.0f},
                                { 1.0f, 1.0f,-1.0f, 1.0f}},

                               {{ 1.0f,-1.0f,-1.0f, 1.0f},
                                { 1.0f, 1.0f,-1.0f,-1.0f},
                                { 1.0f,-1.0f, 1.0f,-1.0f},
                                { 1.0f, 1.0f, 1.0f, 1.0f}}};

        const float gaps[3][W]={{0.11f, 0.17f, 0.23f, 0.29f}, // Sexy
                                {0.11f, 0.23f, 0.29f, 0.41f}, // Sophie German
                                {1.00f/ 9.00f, 1.00f/ 7.00f,
                                 1.00f/ 5.00f, 1.00f/ 3.00f}}; // Odd Harmonics 
        inline void init();
        inline float process(const float&);
        reverb();
};

inline reverb::reverb()
{
    init();
    limit.threshold = 0.8;
}

inline void reverb::init()
{
    for(int i=0; i<W; i++)
    {
        d[i].tone       = &tone;
        T[i]            = (scale * 3 + 0.1f) * gaps[1][i];
        d[i].time       = &T[i];
        d[i].feedback   = feedback * 0.8f;
        d[i].amount     = amount * 0.8f;
    }
}

inline float reverb::process(const float& in)
{
    hh.iterate();
    float out   = in;
    float R     = 0.0f;
    theta       = -1.0f;
    for(int i=0; i<W; i++) feed[i] = 0.0f;

    for(int y=0; y<W; y++)
    {
        for(int x=0; x<W; x++)
        {
            f[x].a   = theta; // All pass init
            out      = f[x].process(fDD[2](&d[x], in + feed[y]));
            out     *= e;
            feed[y] += (out * H[x][y][y]);

            theta+=phi; // All Pass angle increment
        }
        feed[y] *= e;
        R += feed[y];
    }

    return R;
}
