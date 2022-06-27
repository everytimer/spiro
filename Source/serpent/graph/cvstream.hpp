////////////////////////////////////////////////////////////////////////////////////////
// Circular Vector Stream TINT
// V.0.0.1 31-12-2021
////////////////////////////////////////////////////////////////////////////////////////
#ifndef CVSTREAM
#define CVSTREAM

#include <vector>
#include <cstdlib>
using std::vector;



class cvstream
{
    private:
        std::vector<uint*>      data;
        int                     width;                      // Number of frames
        int                     size;                       // Buffer size
        int                     current;                    // Frame counter
        
    public:
        inline uint *at();                                  // Return current frame
        inline uint *at(int);                               // Return frame at give position
        inline void set (uint*);                            // Fill current frame
        inline void set (uint*, int);                       // Fill frame at give position
        inline void next ();                                // Next frame
        inline void prior();                                // Previous frame
        inline void clear();                                // Clear current frame
        inline void flush();                                // Clear buffer
        inline int  frames_count();
        inline int  buffer_size();
        cvstream(int, int);
        ~cvstream();
};

inline uint *cvstream::at(){
        return data[current];
}

inline uint *cvstream::at(int position){
        int f = position;
        f>=width? f%=width: f;
        return data[f];
}

inline void cvstream::set (uint* d){
        for(int i= 0; i< size; i++)
        {
            data[current][i]=d[i];
        }
}

inline void cvstream::set (uint* d, int position){
        int f= position;
        f>=width? f%=width: f;
        for(int i= 0; i< size; i++)
        {
            data[f][i]=d[i];
        }
}

inline void cvstream::next() 
{ 
        current++;
        current==width? current= 0: current;
}

inline void cvstream::prior() 
{ 
        current--;
        current<0? current= width: current;
}

inline void cvstream::clear()
{
        for(int i= 0; i< size; i++)
        {
            data[current][i]= .0;
        }
}

inline void cvstream::flush()
{
        for(int i= 0; i< width; i++)
        {
            this->next();
            this->clear();
        }
}

inline int  cvstream::frames_count()
{
        return width;
}
inline int  cvstream::buffer_size()
{
        return size;
}

cvstream::cvstream(int bsize, int nframes)
{ 
        width= nframes;
        size = bsize;
        data.reserve(width);
        for(int i=0; i< width; i++)
        {
            data.push_back(new uint[size]);
        }
        current= 0;
}

cvstream::~cvstream() 
{
        for(int i=0; i< width; i++)
        {
            delete data[i];
        }
}

#endif

