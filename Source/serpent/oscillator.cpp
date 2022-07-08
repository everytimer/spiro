////////////////////////////////////////////////////////////////////////////////////////
// oscillator
// V.0.3.7 2022-06-15
////////////////////////////////////////////////////////////////////////////////////////
#include "oscillator.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void cell::oscillator::retrigger()
{ 
        phase = 0.0f;
}

void cell::oscillator::set_delta(const float Hz)
{ 
        frequency = Hz;
        delta = frequency * TAO / settings->sample_rate; 
}

void cell::oscillator::set_delta()
{ 
        delta = frequency * TAO / settings->sample_rate; 
}

void cell::oscillator::set_shift()
{
        range  = (frequency * CHROMATIC_RATIO - frequency / CHROMATIC_RATIO) * TAO / settings->sample_rate;
        delta += (shift - 0.5f) * range * 2.0f;
}

void cell::oscillator::reset()
{
        set_delta();
        set_shift();
}

cell::oscillator::oscillator(iospecs* io): settings(io)
{
        reset();
}

// Init Settings before setting delta[0]
cell::oscillator::oscillator()
{

}


void cell::oRotor(oscillator* o)
{       
        o->out.y = o->phase;
        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}
////////////////////////////////////////////////////////////////////////////////////////
// Waveforms: VCO //////////////////////////////////////////////////////////////////////

void cell::oSine(oscillator* o)
{       
        o->out.y = sin(o->phase) * *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}


void cell::oParabol(oscillator* o)
{ 
        static bool s;

        float f = o->phase * o->phase;
        !s ? f = PI2 - f : f = f - PI2;

        o->out.y = f / PI2 * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) { o->phase -= TAO; s = !s; }
}

// void cell::fParabol(oscillator* o)
// { 
//         static bool s;
//         float f = o->phase * o->phase;
//         !s ? f = PI2 - f : f = f - PI2;

//         o->out.y = f / PI2 * o->amplitude * o->am;

//         o->phase += o->delta + o->fm;
//         if(o->phase >= PI) { o->phase -= TAO; s = !s; }
// }


void cell::oNoise(oscillator* o)
{
        static float x, y;
        if(y == 0.0f) x = y = 1;
        y = sin((x += o->delta) * y);
        o->out.y = y * *o->amplitude;
}

void cell::oAdditive(oscillator* o)
{
        o->out.x = 0.0f;
        o->out.y = 0.0f;
        for(int i = 0; i < o->o->size; i++)
        {
                o->out.y += sin(o->phase * (i + 1)) * o->o->data[i] / (i+1);
                o->out.x += cos(o->phase * (i + 1)) * o->o->data[i] / (i+1);
        }
        o->out.x *= *o->amplitude;
        o->out.y *= *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}



void cell::oRamp(oscillator* o) 
{
        o->out.y = 0;
        for(int i = 1; i <= o->nharm; i++)
        {
                o->out.y += sin(o->phase * i + PI) / i;
        }
        o->out.y *= *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}

void cell::oSawtooth(oscillator* o) 
{
        o->out.y = 0;
        for(int i = 1; i <= o->nharm; i++)
        {
                o->out.y += sin(o->phase * i) / i;
        }
        o->out.y *= *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}

void cell::oSquare(oscillator* o)
{
        float pw = (*o->pwm * 1.9f + 0.05f) * PI;
        float ax = 0, bx = 0;

        for(int i = 1; i <= o->nharm; i++)
        {
                ax += sin(o->phase * i) / i;
                bx += sin((o->phase + pw) * i) / i;
        }
        o->out.y = (ax - bx) * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}

void cell::oParabolic(oscillator* o)
{
        float pw = (*o->pwm * 1.9f + 0.05f) * PI;
        float ax = 0;

        for(int i = 1; i <= o->nharm; i++) ax += cos(o->phase * i) / (i * i);

        o->out.y = ax * *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}

void cell::oSquare2D(oscillator* o)
{
        float pw = (*o->pwm * 1.9f + 0.05f) * PI;
        float ax = 0, bx = 0;
        float ay = 0, by = 0;
        for(int i = 1; i <= o->nharm; i++)
        {
                ax += sin(o->phase * i) / i;
                bx += sin((o->phase + pw) * i) / i;

                ay += cos(o->phase * i) / i;
                by += cos((o->phase + pw) * i) / i;
        }
        o->out.y = (ax - bx) * *o->amplitude;
        o->out.x = (ay - by) * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}

void cell::oTomisawa(oscillator* o)
{
        o->ecx = 1.0f;                  
        o->ecx *= 1.0f * (1 - 0.0001f * o->frequency); 
        if(o->ecx < 0) o->ecx = 0;

        o->phase += o->delta + *o->fm;                
        if(o->phase >= PI) o->phase -= TAO;             

        float oa = cos(o->phase + (o->shift - 0.5f) * TAO + o->ecx * o->eax); 
        o->eax = 0.5f*(oa + o->eax);        

        float ob = cos(o->phase + (o->shift - 0.5f) * TAO + o->ecx * o->ebx + (*o->pwm * 1.9f + 0.05f) * PI); 
        o->ebx = 0.5f * (ob + o->ebx);            
        o->out.y = (oa - ob) * *o->amplitude;
}

void cell::oTriangle(oscillator* o)
{
        float rise = *o->pwm * TAO;
        float fall = TAO - rise;
        float rise_delta = (rise != 0.0f) ? (2.0f * *o->amplitude / rise) : 0.0f;
        float fall_delta = (fall != 0.0f) ? (2.0f * *o->amplitude / fall) : 0.0f;

        if (o->phase > TAO) o->phase -= TAO;
        if (o->phase < rise) o->out.y = - *o->amplitude + sqrt(o->phase) * rise_delta;
        else o->out.y = *o->amplitude - (sqrt(o->phase) - rise) * fall_delta;
        o->phase += o->delta + *o->fm;
}


void cell::oGinger(oscillator* o)     // Add warp ????
{
        static gingerbreadman g;
        g.x =   o->phase;
        g.y*= (*o->pwm - 0.5f) * 2.0f;
        g.iterate();
        o->out.y = (g.x - 2.5f) * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oIkeda(oscillator* o)     // *
{
        static ikeda i;
        i.x =  o->phase;
        i.u = (0.979999f + *o->pwm/50.0f);
        
        i.iterate();
        o->out.y = (i.y + i.x * o->phase) * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}


void cell::oDuffing(oscillator* o)     // *
{
        static duffing d;
        d.y =  o->phase;
        //d.t = o->delta/10;
        d.a = *o->pwm*16.0f;
        d.iterate();
        o->out.y = (d.y*0.1f) * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}



void cell::oFabrikant(oscillator* o)     
{
        static rabinovich_fabrikant d;
        static dcb f;
        d.x = o->phase;
        d.gamma = (0.979999f +o->phase/50.0f);
        d.x *= (1.0f + *o->pwm);
        //d.gamma = 0.999999;
        //d.alpha = (o->pwmcv-0.5)*8;
        d.iterate();
        o->out.y = 5 * (f.process((d.x+d.y+d.z)*0.002f* *o->amplitude*(1.01-*o->pwm)*(1.2-o->phase)));

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oVanDerPol(oscillator* o)// OK
{
        static vanderpol d;

        d.t = o->delta / 3.0f;
        d.f = o->phase * 2.0f;
        //d.a = 10.0f + o->phasecv*2;
        d.iterate();
        
        o->out.y = ( xfade( d.y, d.x, *o->pwm )) * *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}



////////////////////////////////////////////////////////////////////////////////////////
// 3D //////////////////////////////////////////////////////////////////////////////////

void cell::oSprottST(oscillator* o)
{
        static sprott_st s;

        s.t = o->delta/2.0f;
        s.iterate();
        
        o->out.x = s.x * *o->amplitude;
        o->out.y = s.y * *o->amplitude;
        o->out.z = s.z * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oHelmholz(oscillator* o)
{
        static helmholz d;

        d.t = o->delta/2.0f;
        d.gamma = ((*o->pwm-0.5f)*2.0f)  + 5.11f;
        d.delta = ((o->warp-0.5f)*0.03f) + 0.55f;
        d.iterate();
        
        o->out.x = d.x * *o->amplitude * 3.0f;
        o->out.y = d.y * *o->amplitude * 3.0f;
        o->out.z = d.z * *o->amplitude * 3.0f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oHalvorsen(oscillator* o)
{
        static halvorsen h;

        h.t = o->delta/20.0f;
        h.iterate();
        
        o->out.x = h.x * *o->amplitude * 0.5f;
        o->out.y = h.y * *o->amplitude * 0.5f;
        o->out.z = h.z * *o->amplitude * 0.5f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oTSUCS(oscillator* o)
{
        static tsucs d;
        d.b = *o->pwm   / 2.0f + 0.40f;
        d.e = o->warp  / 8.0f + 0.55f;
        d.t = o->delta / 40.0f;
        d.iterate();

        o->out.x = (d.x) * *o->amplitude * 0.1f;
        o->out.y = (d.y) * *o->amplitude * 0.1f;
        o->out.z = (d.z-28.0f) * *o->amplitude * 0.1f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;

        // o->latitude += o->theta + o->fm;
        // if(o->latitude >= TAO) o->latitude -= TAO;
}


void cell::oLinz(oscillator* o)
{
        static linz l;

        l.t = o->delta;
        l.iterate();
        
        o->out.x = l.x * *o->amplitude;
        o->out.y = l.y * *o->amplitude;
        o->out.z = l.z * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oYuWang(oscillator* o)
{
        static yu_wang yu;

        yu.t = o->delta/40;
        yu.iterate();
        
        o->out.x = yu.x * *o->amplitude;
        o->out.y = yu.y * *o->amplitude;
        o->out.z = yu.z * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oRoessler(oscillator* o)
{
        static roessler rsl;

        rsl.delta = o->delta;
        rsl.iterate();
        
        o->out.x = rsl.x * *o->amplitude * 0.5f;
        o->out.y = rsl.y * *o->amplitude * 0.5f;
        o->out.z = rsl.z * *o->amplitude * 0.5f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oLorenz(oscillator* o)
{
        static lorenz lr;

        lr.t = o->delta;
        lr.iterate();
        
        o->out.x = lr.x * *o->amplitude * 0.25f;
        o->out.y = lr.y * *o->amplitude * 0.25f;
        o->out.z = lr.z * *o->amplitude * 0.25f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oChenLee(oscillator* o)
{
        static chen_lee cl;

        cl.t = o->delta;
        cl.iterate();
        
        o->out.x = cl.x * *o->amplitude * 0.25f;
        o->out.y = cl.y * *o->amplitude * 0.25f;
        o->out.z = cl.z * *o->amplitude * 0.25f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}

void cell::oSphere(oscillator* o)
{       
        float  S = sinf(o->phase);
        o->out.x = cosf(o->latitude) * S * *o->amplitude;
        o->out.y = sinf(o->latitude) * S * *o->amplitude;
        o->out.z = cosf(o->phase) * *o->amplitude;

        o->latitude += o->theta + *o->fm;
        if(o->latitude >= TAO) o->latitude -= TAO;
        
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}


void cell::oCube(oscillator* o)
{       
        float pw = (*o->pwm * 1.9f + 0.05f) * PI;
        float ax(0.0f), bx(0.0f);
        float ay(0.0f), by(0.0f);
        float az(0.0f), bz(0.0f);
        for(int i = 1; i <= o->nharm; i++)
        {
                float  So = sinf(o->phase * i);
                float  Sp = sinf((o->phase + pw) * i);
                float  I  = i * i;
                ax += cosf( o->latitude * i)       * So / I;
                bx += cosf((o->latitude + pw) * i) * Sp / I;

                ay += sinf( o->latitude * i)       * So / I;
                by += sinf((o->latitude + pw) * i) * Sp / I;

                az += cosf( o->phase * i) / i;
                bz += cosf((o->phase + pw) * i) / i;
        }
        o->out.y = (ay - by) * *o->amplitude;
        o->out.x = (ax - bx) * *o->amplitude;
        o->out.z = (az - bz) * *o->amplitude;

        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;

        o->latitude += o->theta + *o->fm;
        if(o->latitude >= TAO) o->latitude -= TAO;
}

void cell::oSaw3D(oscillator* o) 
{
        o->out.x = 0.0f;
        o->out.y = 0.0f;
        o->out.z = 0.0f;
        for(int i = 1; i <= o->nharm; i++)
        {
                float  S = sinf(o->phase * i + *o->pwm * PI);
                float  I  = i * i;
                o->out.x += cosf(o->latitude * i + *o->pwm * PI) * S / I;
                o->out.y += sinf(o->latitude * i + *o->pwm * PI) * S / I;
                o->out.z += cosf(o->phase * i + *o->pwm * PI) / i;
        }
        o->out.x *= *o->amplitude;
        o->out.y *= *o->amplitude;
        o->out.z *= *o->amplitude;
        o->phase +=  o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
        o->latitude += o->theta + *o->fm;
        if(o->latitude >= TAO) o->latitude -= TAO;
}


////////////////////////////////////////////////////////////////////////////////////////
// 2D //////////////////////////////////////////////////////////////////////////////////
void cell::oSine2D(oscillator* o)
{       
        o->out.x = cos(o->phase) * *o->amplitude;
        o->out.y = sin(o->phase) * *o->amplitude;
        o->phase += o->delta + *o->fm;
        if(o->phase >= TAO) o->phase -= TAO;
}

void cell::oKaplanYorke(oscillator* o)
{
        static kaplan_yorke ky;

        ky.t = o->delta;
        ky.iterate();
        
        o->out.x = ky.x * *o->amplitude * 0.25f;
        o->out.y = ky.y * *o->amplitude * 0.25f;

        o->phase += o->delta + *o->fm;
        if(o->phase >= PI) o->phase -= TAO;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////