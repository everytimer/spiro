////////////////////////////////////////////////////////////////////////////////////////
// Circular Audio Buffer 
// V.0.1.1 2022-01-30
////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <vector>
#include <cstdlib>
using std::vector;

namespace cell {

class circular
{
    private:
        float*      data;
        const int   size;           // Buffer size
        int         current;        // Write cursor
        int         prior;          // Read cursor
        void        next(void);     // Next value
        
    public:
        float*   get();                          // Return buffer
        float    at();                           // Return current value
        float    at(const int&);                 // Return value at given position
        void     set(const float&);              // Fill current value
        void     add(const float&, const int&);  // Fill value at shifted position
        void     clear();                        // Clear buffer
        int      length();                       // Get size
        circular(int);
        ~circular();
};



////////////////////////////////////////////////////////////////////////////////////////
// Wavering ////////////////////////////////////////////////////////////////////////////
class wavering
{
    private:
        std::vector<float*> data;
        int nframes;   // Number of frames
        int size;      // Buffer size
        int current;   // Frame counter
        int i;         // Sample counter
        
    public:
        float* at();                // Return current frame
        float* at(int);             // Return frame at given position
        float* shift(int);          // Return frame at position shifted from current
        void set (float*);          // Fill current frame
        void set (float*, int);     // Fill frame at given position
        void next ();               // Next frame
        void prior();               // Previous frame
        void clear();               // Clear current frame
        void flush();               // Clear buffer
        int  frames_count();
        int  buffer_size();
        wavering(const int&, const int&);
        ~wavering();
};

};