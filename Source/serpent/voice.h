#pragma once
#include "oscillator.h"
namespace cell {

class voice
{
    private:
        
    public:
        iospecs*    settings;
        oscillator* vco;
        const int   oscn = 6;
        float note;
        float velocity;
        float bend;
        frame<float>* cvs;
        void trigger(float);
        void init();
        voice(int);
        voice();
       ~voice();
};




};