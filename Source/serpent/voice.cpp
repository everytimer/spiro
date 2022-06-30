#include "voice.h"
namespace cell {

voice::voice(int n = 6): oscn(n)
{
    vco = new oscillator[oscn];

}


voice::~voice()
{
    delete[] vco;
}

};