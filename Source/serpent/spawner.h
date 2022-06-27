////////////////////////////////////////////////////////////////////////////////////////
// SPAWNER 
// V.0.2.2 2022-06-20
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <cstdlib>

#include "containers.hpp"
#include "iospecs.hpp"
#include "oscillator.h"



namespace cell {
////////////////////////////////////////////////////////////////////////////////////////
// Feed the destination audio buffer ///////////////////////////////////////////////////
class spawner
{  
    private:
    public:
        oscillator* vco;
        frame<point3d<float>>* data;  // Buffer
        iospecs* settings;            // System settings
        int oscn = 1;                 // Oscillators quantity
        float   volume = 0.5f;        // Overall amplitude
        unsigned long long departed = 0; // Samples counter
        void spawn();
        void init();
        void free();
        void reset();
        void trigger(float);
        void iterate();
        spawner(frame<point3d<float>>*, iospecs*);
        ~spawner();
};

};