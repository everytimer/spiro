////////////////////////////////////////////////////////////////////////////////////////
// MIT License
// Copyright (c) 2022 unmanned
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdlib>
#include "containers.hpp"
////////////////////////////////////////////////////////////////////////////////////////

namespace cell {

inline void hBlur(frame<float>* data, uint scale = 1)
{
    int range = scale * 2 + 1;
    for(uint y = 0; y < data->height; y++)
    {
        for(uint x = 0; x < data->width-range; x++)
        {
            float car = 0.0f;
            for(int i = 0; i < range; i++)
            {   
                car += data->get(x + i, y);
            }
            car /= range;
            data->set(x + scale, y, car);
        }
    }
}

inline void vBlur(frame<float>* data, uint scale = 1)
{
    int range = scale * 2 + 1;  
    for(uint x = 0; x < data->width; x++)
    {
        for(uint y = 0; y < data->height-range; y++)
        {
            float car = 0.0f;
            for(int i = 0; i < range; i++)
            {   
                car += data->get(x, y + i);
            }
            car /= range;
            data->set(x, y + scale, car);
        }
    }
}

inline void boxBlur(frame<float>* data, uint scale = 1, float f = 0.0f)
{
    int range = scale * 2 + 1;
    for(uint y = 0; y < data->height; y++)
    {
        for(uint x = 0; x < data->width-range; x++)
        {
            float car = 0.0f;
            for(int i = 0; i < range; i++)
            {   
                car += data->get(x + i, y);
            }
            car /= float(range)+f;
            data->set(x + scale, y, car);
        }
    }
    
    for(uint x = 0; x < data->width; x++)
    {
        for(uint y = 0; y < data->height-range; y++)
        {
            float car = 0.0f;
            for(int i = 0; i < range; i++)
            {   
                car += data->get(x, y + i);
            }
            car /= float(range)+f;
            data->set(x, y + scale, car);
        }
    }
}


inline void alphaGradientFrame(frame<float>* data, uint n)
{
    float d = 1.0f/float(n);
    float f = 1.0f;

    for(uint y = (data->height-n); y < data->height; y++)
    {
        f -= d;
        for(uint x = 0; x < data->width; x++)
        {
            data->set(x, y, data->get(x, y)*f);
        }
    }
    f = 1.0f;
    for(uint y = n; y > 0; y--)
    {
        f -= d;
        for(uint x = 0; x < data->width; x++)
        {
            data->set(x, y, data->get(x, y)*f);
        }
    }
    f = 1.0f;
    for(uint x = (data->width-n); x < data->width; x++)
    {
        f-=d;
        for(uint y = 0; y < data->height; y++)
        {
            data->set(x, y, data->get(x, y)*f);
        }
    }
    f = 1.0f;
    for(uint x = n; x > 0; x--)
    {
        f-=d;
        for(uint y = 0; y < data->height; y++)
        {
            data->set(x, y, data->get(x, y)*f);
        }
    }
}


};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
