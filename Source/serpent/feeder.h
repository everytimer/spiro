////////////////////////////////////////////////////////////////////////////////////////
// CALLBACK WRAPPER / IO Interface
// V.0.0.3 Copyright (c) 2021 - 2022 unmanned
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <cstdint>
#include <cstdlib>

#include "preset.h"
#include "iospecs.hpp"
#include "containers.hpp"
#include "spawner.h"
#include "midi.hpp"

namespace cell {

////////////////////////////////////////////////////////////////////////////////////////
// Feed the destination audio buffer ///////////////////////////////////////////////////
class feeder
{
    private:
        bool standby = true;
        void free();
        void init();
        void bind();

    public:
        spawner* renderer;
        frame<point3d<float>>* data;
        iospecs settings;
        preset  io;
        void trigger(message*);
        void process();                         // Render audio
        void reset();
        feeder(iospecs*);
        feeder();
       ~feeder();
};

};