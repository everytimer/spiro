////////////////////////////////////////////////////////////////////////////////////////
// MIDI WRAPPER
// V.0.0.1 Copyright (c) 2022 unmanned
////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>
#include "scale_converter.hpp"

namespace cell {

struct message
{
    enum type { NoteON, NoteOFF };
    type mode;
    unsigned note;
    unsigned channel;
    float velocity;
    float detune;
    float modwheel;
    unsigned id;
};



};