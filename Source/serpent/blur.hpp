////////////////////////////////////////////////////////////////////////////////////////
// MIT License
// Copyright (c) 2022 unmanned
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdlib>
#include "containers.hpp"
////////////////////////////////////////////////////////////////////////////////////////

namespace cell {

void hBlur(frame<float>* data, uint scale = 1)
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

void vBlur(frame<float>* data, uint scale = 1)
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

void boxBlur(frame<float>* data, uint scale = 1)
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

};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
