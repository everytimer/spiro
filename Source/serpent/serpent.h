////////////////////////////////////////////////////////////////////////////////////////
// SERPENT - Algorhithmic sequencer
// V.0.0.1 2022-01-14
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "scales.hpp"
#include "scale_converter.hpp"
#include "chaos.hpp"
#include "automata.h"
using std::vector;
using std::string;


namespace cell {
////////////////////////////////////////////////////////////////////////////////////////
// Collatz /////////////////////////////////////////////////////////////////////////////
vector<float> fsC3N1(uint, uint, uint, const vector<float>&);
vector<float> fsLorenz(uint, uint, uint, const vector<float>&);
vector<float> fsLangtons(uint, uint, uint, const vector<float>&);

uint frC3N1(uint);
uint frLorenz(uint);
uint frLangtons(uint);
// Arguments are: 1) Number of elements
//                2) Seed
//                3) Scale
//                4) Octaves above
inline vector<float> (*fF[])(uint, uint, uint, const vector<float>&) = { fsC3N1, fsLorenz };
////////////////////////////////////////////////////////////////////////////////////////
// Rhythm patterns /////////////////////////////////////////////////////////////////////
inline uint          (*fR[])(uint) = { frC3N1, frLorenz, frLangtons };
////////////////////////////////////////////////////////////////////////////////////////
// SERPENT /////////////////////////////////////////////////////////////////////////////
class serpent
{
    private:
    public:
        uint            in = 0;         // Current note position
        uint            is = 0;         // Current step position
        vector<float>   scale;          // Initial sequence 
        vector<float>   sequence;       // Playback
        vector<float>   timeline;       // Absolute trigger values in ms  
        uint*           departed;       // Current sample 
        uint            pattern;        // Pattern in bit representation

    public:
        friend          class spawner;
        uint            offset;         // Time at step #0
        float           A4 = 440.0f;    // Microtune
        uint            octaves = 1;    // Range above root
        uint            key     = 0;    // Root note : 0 means A
        float           seed[2];        // Initial condition for [0] Sequence and [1] beat
        float           note = 0;       // Current note
        uint            step = 0;       // Current step
        uint            length  = 0;    // Sequence length in samples
        uint            steps   = 32;   // Number of steps in beat
        int             divisor = 1;    // Beat divisor
  
        void init();                                    // Goto sequence front
        void next();                                    // Next sequence & timeline breakpoint
        void prior();                                   // Previous breakpoint
        void set(const string&);                        // Set new scale from string input
        void timeset(const float&);                     // Generate rhythm pattern of given length using bitset
        void regenerate(uint);                          // Generate new sequence from given scale using fF 
        serpent(const string&, uint, const uint&);      // Arguments are: scale sring, time in ms, rhythm pattern
        serpent() {};
       ~serpent();
};


uint beat_divide(const uint&, const int&);

};