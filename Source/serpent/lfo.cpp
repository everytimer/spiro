////////////////////////////////////////////////////////////////////////////////////////
// LFO Waveforms
// V.0.3.9 2022-06-15
////////////////////////////////////////////////////////////////////////////////////////
#include "oscillator.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


void cell::lfoSine(cell::oscillator* o)
{
        o->out.y = sinf(tanf(sinf(o->phase) * (o->warp - 0.5f) * 3.0f)) * *o->amplitude;
        o->phase += o->delta;
        if(o->phase >= TAO)
        o->phase -= TAO;
}


void cell::lfoMorphSine(cell::oscillator* o)
{
        o->out.y = sinf(sinf(o->phase) * (o->warp - 0.5f) * TAO) * *o->amplitude;
        o->phase += o->delta;
        if(o->phase >= TAO)
        o->phase -= TAO;
}


void cell::lfoSaw(cell::oscillator* o) 
{
        o->out.y = ( 1.0f - 2.0f * o->phase * ITAO) * *o->amplitude;
        o->phase += o->delta;
        if(o->phase >= TAO)
        o->phase -= TAO;   
        if(o->phase < 0.0f)
        o->phase += TAO;
}


void cell::lfoTriangle(cell::oscillator* o)
{
        o->out.y = tan(sin(o->phase)) * *o->amplitude*0.65f;
        o->phase += o->delta;
        if(o->phase >= TAO)
        o->phase -= TAO;
}


void cell::lfoMorphTri(cell::oscillator* o)
{
        float rise = o->warp * TAO;
        float fall = TAO - rise;
        float rise_delta = (rise != 0) ? (2.0 * *o->amplitude / rise) : 0;
        float fall_delta = (fall != 0) ? (2.0 * *o->amplitude / fall) : 0;

        if (o->phase > TAO)  o->phase -= TAO;
        if (o->phase < rise) o->out.y = - *o->amplitude + o->phase * rise_delta;
        else o->out.y = *o->amplitude - (o->phase - rise) * fall_delta;
        o->phase += o->delta;
}


void cell::lfoLorenzX(cell::oscillator* o)
{
        static dcb d; 
        d.f = 0.82f;
        static lorenz l;
        l.a = o->delta*16 + 8;
        l.t = o->warp * o->warp * o->warp/200.0f;
        l.iterate();
        o->out.y = d.process(l.x * 0.2f);
}


void cell::lfoIkeda(cell::oscillator* o)
{
        static ikeda i;
        static dcb d; 
        
        d.f = 0.82f;
        i.x =  o->phase;
        i.u = (0.979999f + o->warp / 50.0f);
        
        i.iterate();
        o->out.y = d.process((i.y + i.x * o->warp)) * *o->amplitude * 0.20f;

        o->phase += o->delta;
        if(o->phase >= M_PI) o->phase -= TAO;
}



void cell::lfoRoesslerX(cell::oscillator* o)
{
        static roessler rsl;
        rsl.delta = o->delta / 32;
        rsl.c = o->warp * 7.7f + 1.0f;
        rsl.iterate();

        o->out.y = rsl.x * 0.05f;
}



std::vector<float> imprint(cell::oscillator* l, int width, int step)
{
        l->settings->sample_rate = width / 2;
        l->set_delta();
        std::vector<float> r(width, 0);
        int i = 0;
        while (i < width)
        {
            cell::form[(int)*l->form](l);
            r[i] = l->out.y;
            i++; 
        }               
        return r;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////