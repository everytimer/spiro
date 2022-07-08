////////////////////////////////////////////////////////////////////////////////////////
// SPAWNER - Interface
// V.0.2.2 2022-06-20
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <cstdlib>

#include "containers.hpp"
#include "iospecs.hpp"
#include "voice.h"



namespace cell {
////////////////////////////////////////////////////////////////////////////////////////
// Feed the destination audio buffer ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// CVS - Control values ////////////////////////////////////////////////////////////////
// cvs[oscillator][]
class spawner
{  
    private:
    public:
        voice* v;
        frame<point3d<float>>* data;    // Buffer
        frame<float>* cvs;              // Control values
        iospecs* settings;              // System settings
        float volume = 0.5f;            // Overall amplitude
        uint  departed = 0;             // Samples counter
        const int poly;                 // Polyphony

        float angle[3];
        void spawn();
        void init();
        void free();
        void reset();
        void trigger(int, float);
        void iterate();
        spawner(frame<point3d<float>>*, iospecs*, const int);
        ~spawner();
};

};