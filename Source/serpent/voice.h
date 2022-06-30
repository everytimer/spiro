#pragma once
#include "oscillator.h"
namespace cell {

class voice
{
    private:
        
    public:
        oscillator* vco;
        const int oscn;
        voice(int);
       ~voice();
};




};