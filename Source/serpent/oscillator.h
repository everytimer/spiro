////////////////////////////////////////////////////////////////////////////////////////
// Oscillator
// V.0.3.7 2022-06-15
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cmath>
#include "containers.hpp"
#include "envelopes.h"
#include "constants.hpp"
#include "iospecs.hpp"
#include "chaos.hpp"
#include "utility.hpp"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
namespace cell {

class oscillator
{
    public: 
        envelope* env = nullptr;
        iospecs*  settings  = nullptr;
        sequence<float>* o = nullptr; // Harmonics table
        sequence<float>* w = nullptr; // Wave table
        int     nharm = 16;           // Number of harmonics
        float   phase = 0.0f;         // Current phase
        float   delta = 0.0f;         // Phase increment
        float   theta = 0.0f;         // Latitude increment
        float   latitude = 0.0f;
        float   frequency = 440.0;    // Frequency in Hz
        float   amplitude = 0.2f;     // Overall amplitude
        float   eax, ebx, ecx;        // Feedback memory
        float   fm = 0.0f;            // Frequency modulation
        float   pm = 0.0f;            // Phase modulation
        float   am = 1.0f;            // Amplitude modulation
        float   pwm   = 0.5f;         // Pulse width modulation: 0 < 1 
        float   warp  = 0.5f;         // Form dependent modulation: 0 < 1
        float   shift = 0.5f;         // Pitch bend: 0 < 1 
        float   range = 0.0f;         // Pitch shift range
        bool    on = false;           // On / Off flag
        bool    sync = false;         // Reset phase on attack
        int     form = 0;             // Form function id
        point3d<float> out;           // Output: x, y, z
        void    retrigger();
        void    set_delta(const float);
        void    set_delta();
        void    set_shift();
        void    reset();

        oscillator(iospecs*);
        oscillator();
}; 


/////////////////////////////////////////////////
// 1D ///////////////////////////////////////////
void oSine(oscillator*);
void oRamp(oscillator*);
void oSawtooth(oscillator*);
void oSquare(oscillator*);
void oTomisawa(oscillator*);
void oTriangle(oscillator*);
void oGinger(oscillator*);
void oIkeda(oscillator*);
void oDuffing(oscillator*);
void oFabrikant(oscillator*);
void oVanDerPol(oscillator*);
void oParabol(oscillator*);
void oParabolic(oscillator*);
void oNoise(oscillator*);
void oAdditive(oscillator*);

/////////////////////////////////////////////////
// 3D ///////////////////////////////////////////
void oTSUCS(oscillator*);
void oHelmholz(oscillator*);
void oHalvorsen(oscillator*);
void oSprottST(oscillator*);
void oLinz(oscillator*);
void oYuWang(oscillator*);
void oRoessler(oscillator*);
void oLorenz(oscillator*);
void oChenLee(oscillator*);
void oSphere(oscillator*);
void oCube(oscillator*);
void oSaw3D(oscillator*);

/////////////////////////////////////////////////
// 2D ///////////////////////////////////////////
void oSine2D(oscillator*);
void oSquare2D(oscillator*);
void oKaplanYorke(oscillator*);


void lfoSine(oscillator*);
void lfoMorphSine(oscillator*);
void lfoSaw(oscillator*);
void lfoTriangle(oscillator*);
void lfoMorphTri(oscillator*);
void lfoLorenzX(oscillator*);
void lfoIkeda(oscillator*);
void lfoRoesslerX(oscillator*);

std::vector<float> imprint(oscillator*, int, int);


inline void (*form[])(oscillator*) = 
{    
        // 3D //////////////
        oSphere,        // 0
        oCube,          // 1
        oSaw3D,         // 2
        oTSUCS,         // 3
        oHelmholz,      // 4
        oHalvorsen,     // 5
        oSprottST,      // 6
        oLinz,          // 7
        oYuWang,        // 8
        oRoessler,      // 9
        oLorenz,        // 10
        oChenLee,       // 11
        // 2D ///////////////
        oSine2D,        // 26
        oSquare2D,      // 27
        oKaplanYorke,   // 26
        // 1D //////////////
        oSine,          // 0
        oRamp,          // 1
        oSawtooth,      // 2
        oSquare,        // 3
        oTomisawa,      // 4
        oTriangle,      // 5
        oGinger,        // 6
        oIkeda,         // 7
        oDuffing,       // 8
        oFabrikant,     // 9
        oVanDerPol,     // 10
        oParabol,       // 11
        oParabolic,     // 12
        oNoise,         // 13
        oAdditive,      // 14
        // LFOs /////////////
        lfoSine,        //
        lfoSaw,         //
        lfoMorphTri,    //
        lfoTriangle,    //
        lfoLorenzX,     //
        lfoIkeda,       //
        lfoRoesslerX    //
};

};

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////