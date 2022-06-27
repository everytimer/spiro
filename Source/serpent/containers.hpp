////////////////////////////////////////////////////////////////////////////////////////
// Containers
// V.0.1.2 2022-06-20 (C) Unmanned
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace cell {
////////////////////////////////////////////////////////////////////////////////////////
// 3D Point ////////////////////////////////////////////////////////////////////////////
template <typename T>
struct point3d
{
    T x;
    T y;
    T z;
};

////////////////////////////////////////////////////////////////////////////////////////
// 2D Point ////////////////////////////////////////////////////////////////////////////
template <typename T>
struct point2d
{
    T x;
    T y;
};

////////////////////////////////////////////////////////////////////////////////////////
// Square //////////////////////////////////////////////////////////////////////////////
template <typename T>
struct square
{
    T xCentre;
    T yCentre;
    T radius;
};

////////////////////////////////////////////////////////////////////////////////////////
// Sequence ////////////////////////////////////////////////////////////////////////////
template <typename T>
struct sequence
{
    int size = 128;
    T*  data;
    sequence() { data = new T[size]; }
    sequence(int n): size(n) { data = new T[size]; }
   ~sequence() { delete[] data; }
};

////////////////////////////////////////////////////////////////////////////////////////
// Frame ///////////////////////////////////////////////////////////////////////////////
template <typename T>
class frame
{
    private:
        T* data;
    public:   
        const unsigned width;
        const unsigned height;             
        void set(unsigned, unsigned, T);
        T    get(unsigned, unsigned) const;
        T*   ref() const { return data; }
        void clr(T);
        frame(unsigned, unsigned);
       ~frame();
};


template <typename T>
inline void frame<T>::set(unsigned x, unsigned y, T value)
{
    if(((x >= 0) && (x < width)) && ((y >= 0) && (y < height)))
    data[x + y * width] = value;
}

template <typename T>
inline T frame<T>::get(unsigned x, unsigned y) const
{
    if(((x >= 0) && (x < width)) && ((y >= 0) && (y < height))) return data[x + y * width];
    return data[0];
}

template <typename T>
inline void frame<T>::clr(T value)
{
    for(unsigned i = 0; i < (height * width); ++i) data[i] = value;
}

template <typename T>
inline frame<T>::frame(unsigned x, unsigned y): width(x), height(y)
{
    data = new T[height * width];
}

template <typename T>
inline frame<T>::~frame()
{
    delete[] data;
}

////////////////////////////////////////////////////////////////////////////////////////
// Wavering ////////////////////////////////////////////////////////////////////////////
template <typename T>
class wavering
{
    private:
        T* data;
        const unsigned segments = 1024;
        unsigned  i = 0; // Write Pointer
        unsigned  o = 0; // Read Pointer
    public:
        void set(T);
        T get();
        wavering() { data = new T[segments]; }
        wavering(int n): segments(n) { data = new T[segments]; }
       ~wavering() { delete[] data; }
};

template <typename T>
inline void wavering<T>::set(T value)
{
    i++;
    if (i >= segments) i = 0;
    data[i] = value;
}

template <typename T>
inline T wavering<T>::get()
{
    o++;
    if (o >= segments) o = 0;
    return data[o];
}

};