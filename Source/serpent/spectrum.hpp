////////////////////////////////////////////////////////////////////////////////////////
// MIT License
// Copyright (c) 2022 unmanned
//
//  Based on: https://hackaday.io/project/16615-spectrum-analyser-code
//  https://github.com/pramasoul/jrand/blob/master/spectre.c
////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>
#include "constants.hpp"
////////////////////////////////////////////////////////////////////////////////////////

namespace cell {

struct spectre
{
    enum    window { STRAIGHT, HANN, HAMMING, BLACKMAN };
    window  mode = HAMMING;
    const int width;
    const int sample_rate;
    float   precision;
    float*  in;
    float*  data;
    float*  out;
    float   eax;
    float   ebx;
    float   fmax;

    inline void    process();
    inline void    clr();

    inline spectre();
    inline spectre(const int, const int);
    inline ~spectre();
    
};

void spectre::process()
{
    for(int i=0; i<width; i++) // Generate window
    {
        if      (mode == STRAIGHT)  data[i] = in[i]; // Straight Goertzel
        else if (mode == HANN)      data[i] = in[i] * (0.50f - 0.25f * cos(2.0f * M_PI * i/width)); // Hanning Window
        else if (mode == HAMMING)   data[i] = in[i] * (0.54f - 0.46f * cos(2.0f * M_PI * i/width)); // Hamming Window
        else if (mode == BLACKMAN)  data[i] = in[i] * (0.426551f - 0.496561f * cos(2.0f * M_PI * i/width) + 0.076848f * cos(4.0f * M_PI * i/width)); // Exact Blackman Window        
    }
    for(float freq = 0; freq <= fmax; freq += precision) // Scan frequencies
    {
        float f = 2.0 * cos((TAO * (0.5 + ((width * freq) / sample_rate))) / width);
        ebx     = 0.0f;
        eax     = 0.0f;
        for(int i = 0; i < width; i++) 
        {
            float q = f * eax - ebx + data[i];
            ebx = eax;
            eax = q;
        }
        float magnitude = eax * eax + ebx * ebx - eax * ebx * f;
        int   n = round(((freq - fmax / 2) * width / fmax + width / 2));
        out[n]  = magnitude * 5;
    }
}

void spectre::clr()
{
    for(int i = 0; i<width; i++)
    {
        out[i]  = 0.0f;
        data[i] = 0.0f;
    }
}

spectre::spectre(): width(1024), sample_rate(48000)
{
    out       = new float[width];
    data      = new float[width];
    precision = sample_rate / width / 2;
    fmax      = sample_rate / 2.0f;
    clr();
}

spectre::spectre(const int w, const int sr): width(w), sample_rate(sr)
{
    out       = new float[width];
    data      = new float[width];
    precision = sample_rate / width / 2;
    fmax      = sample_rate / 2.0f;
    clr();
}

spectre::~spectre()
{
    clr();
    delete out;
    delete data;
}




};


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////