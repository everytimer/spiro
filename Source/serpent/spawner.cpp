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

        form[0](&v[0].vco[0]);
        form[0](&v[0].vco[1]);
        form[0](&v[0].vco[2]);
        *v[0].vco[0].fm = v[0].vco[2].out.y*0.01;
        // point3d<float> C { v[0].vco[0].out.y, v[0].vco[1].out.y, v[0].vco[2].out.y };
        point3d<float>  C = sphericalToCartesian(v[0].vco[0].out.y, v[0].vco[1].out.y);
        auto o = Rotate(C, angle[0], angle[1], angle[2]);
        // auto o = v[0].vco[1].out;
        o.x *= volume;
        o.y *= volume;
        o.z *= volume;
        data->set(i, 0, o);
    }
}

void cell::spawner::iterate()
{

}


void cell::spawner::trigger(int o, float Hz)
{
    v[0].vco[o].frequency = Hz;
    v[0].vco[o].reset();
}



void cell::spawner::init()
{
    v   = new voice[poly];
    cvs = new frame<float>(v->oscn, 6);
    cvs->clr(0.0f);
    for(int i = 0; i < poly; i++) 
    {
        v[i].settings = settings;
        v[i].cvs = cvs;
        v[i].init();
    }
}

void cell::spawner::free()
{
    delete cvs;
    delete[] v;
}

cell::spawner::spawner(frame<point3d<float>>* buffer, iospecs* io, const int p = 8): data(buffer), settings(io), poly(p)
{
    init();
}

cell::spawner::~spawner()
{
    free();
}