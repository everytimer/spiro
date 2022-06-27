////////////////////////////////////////////////////////////////////////////////////////
// SPAWNER 
// V.0.2.1 2022-01-24
////////////////////////////////////////////////////////////////////////////////////////
#include "spawner.h"


////////////////////////////////////////////////////////////////////////////////////////
// Destination buffer setter ///////////////////////////////////////////////////////////
void cell::spawner::spawn()
{
    for(int i = 0; i < settings->buffer_size; i++)
    {
        form[25](&vco[0]);
        vco[0].out.x *= volume;
        vco[0].out.y *= volume;
        vco[0].out.z *= volume;
        data->set(i, 0, vco[0].out);
    }
}

void cell::spawner::iterate()
{

}


void cell::spawner::trigger(float Hz)
{
    vco[0].frequency = Hz;
    vco[0].reset();
}

void cell::spawner::init()
{
    vco = new oscillator[oscn];
    for(int i = 0; i < oscn; i++)
    {
        vco[i].settings = settings;
        vco[i].reset();
    }
}

void cell::spawner::free()
{
    delete vco;
}

cell::spawner::spawner(frame<point3d<float>>* buffer, iospecs* io): data(buffer), settings(io)
{
    init();
}

cell::spawner::~spawner()
{
    free();
}