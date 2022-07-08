////////////////////////////////////////////////////////////////////////////////////////
// CALLBACK WRAPPER / IO Interface
// V.0.0.3 Copyright (c) 2021 - 2022 unmanned
////////////////////////////////////////////////////////////////////////////////////////

#include "feeder.h"


void cell::feeder::trigger(cell::message* msg)
{
    if(msg->mode = cell::message::NoteON)
    {
        renderer->v[0].vco[0].set_delta(cell::note_to_hz(msg->note));
    }
}



void cell::feeder::init()
{
        std::cout << ":: Feeder ::\t" << "\n";
        std::cout << "Sample rate:\t" << settings.sample_rate << "\n";
        std::cout << "Channels   :\t" << settings.channels << "\n";
        std::cout << "Buffer size:\t" << settings.buffer_size << "\n";

        data     = new frame<point3d<float>>(settings.buffer_size, settings.channels);
        renderer = new spawner(data, &settings, 8);
        //renderer->settings = &settings;

        standby  = false;
}

void cell::feeder::bind()
{
        io.volume = &renderer->volume;
}


void cell::feeder::free()
{
        delete renderer;
        delete data;
}

void cell::feeder::reset()
{
        free();
        init();
}

cell::feeder::feeder(iospecs* io): settings(*io)
{
        init();
}

cell::feeder::feeder()
{
        init();
}

cell::feeder::~feeder()
{
        free();
}

void cell::feeder::process()
{
        renderer->spawn();
}