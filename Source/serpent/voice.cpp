#include "voice.h"
namespace cell {

voice::voice(int n): oscn(n)
{
    vco = new oscillator[oscn];
}

void voice::init()
{
    for(int i = 0; i < oscn; i++) 
    {
        vco[i].settings  = settings;
        vco[i].theta     = cvs->get(i, 0);
        vco[i].fm        = cvs->ref(i, 1);
        vco[i].pwm       = cvs->ref(i, 2);
        vco[i].amplitude = cvs->ref(i, 3);
        vco[i].form      = cvs->ref(i, 4);
    }
}

voice::voice()
{
    vco = new oscillator[oscn];
}

voice::~voice()
{
    delete[] vco;
}

};