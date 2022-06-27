////////////////////////////////////////////////////////////////////////////////////////
// Circular Audio Buffer 
// V.0.1.1 2022-01-30
////////////////////////////////////////////////////////////////////////////////////////

#include "wavering.h"
////////////////////////////////////////////////////////////////////////////////////////


void cell::circular::next()
{
        current++;
        prior = current - 1;
        if(current == size)
        {
            current = 0;
            prior = size;
        }
}

float* cell::circular::get()
{
        return data;
}

float cell::circular::at()
{
        return data[prior];
}

float cell::circular::at(const int& i)
{
        int pos = prior + i;
        if(pos > size) pos %= size;
        return data[pos];
}

void cell::circular::set(const float& d)
{
        data[current] = d;
        next();
}

void cell::circular::add(const float& d, const int& shift)
{
        int p = ((current + shift) >= size? (current+shift) % size: (current + shift));
        data[p] += d;
}


void cell::circular::clear()
{
        for(int i = 0; i < size; i++)
        {
            data[i] = 0.0f;
        }
}

int  cell::circular::length()
{
        return size;
}

cell::circular::circular(int s): size(s)
{ 
        data = new float[size];
        clear();
        current = 0;
}

cell::circular::~circular() 
{
        delete data;    
}



////////////////////////////////////////////////////////////////////////////////////////
// Wavering ////////////////////////////////////////////////////////////////////////////

float* cell::wavering::at()
{
        return data[current];
}

float* cell::wavering::at(int position)
{
        position >= nframes ? position %= nframes: position;
        return data[position];
}

float* cell::wavering::shift(int position)
{
        int f = current + position;
        f >= nframes ? f %= nframes: f;
        return data[f];
}

void cell::wavering::set (float* d)
{
        for(int i = 0; i < size; i++)
        {
            data[current][i] = d[i];
        }
}

void cell::wavering::set (float* d, int position)
{
        int f = position;
        f >= nframes ? f %= nframes: f;
        for(int i = 0; i < size; i++)
        {
            data[f][i] = d[i];
        }
}

void cell::wavering::next() 
{ 
        current++;
        current == nframes ? current = 0: current;
}

void cell::wavering::prior() 
{ 
        current--;
        current < 0 ? current = nframes: current;
}

void cell::wavering::clear()
{
        for(int i = 0; i < size; i++)
        {
            data[current][i]= .0;
        }
}

void cell::wavering::flush()
{
        for(int i = 0; i < nframes; i++)
        {
            this->next();
            this->clear();
        }
}

int cell::wavering::frames_count()
{
        return nframes;
}

int cell::wavering::buffer_size()
{
        return size;
}

cell::wavering::wavering(const int& bsize, const int& frames)
{ 
        nframes = frames;
        size  = bsize;
        data.reserve(nframes);
        for(int i = 0; i < nframes; i++)
        {
            data.push_back(new float[size]);
        }
        current = 0;
        i = 0;
}

cell::wavering::~wavering() 
{
        for(int i = 0; i < nframes; i++)
        {
            delete data[i];
        }
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////