// https://github.com/Takemonist/catmull_rom

#pragma once
#include <vector>
#include <cmath>
#include "containers.hpp"
namespace cell {

template<class T>
struct Point
{
    T x;
    T y;
    Point(T a, T b) { x = a;  y = b; }
    Point() {}

    Point operator+(Point v)
    {
        Point r;
        r.x = this->x + v.x;
        r.y = this->y + v.y;
        return r;
    }
    Point operator-(Point v)
    {
        Point r;
        r.x = this->x - v.x;
        r.y = this->y - v.y;
        return r;
    }
    Point operator+(T value)
    {
        Point r;
        r.x = this->x + value;
        r.y = this->y + value;
        return r;
    }
    Point operator-(T value)
    {
        Point r;
        r.x = this->x - value;
        r.y = this->y - value;
        return r;
    }
    Point operator*(T value)
    {
        Point r;
        r.x = this->x * value;
        r.y = this->y * value;
        return r;
    }
    Point operator/(T value)
    {
        Point r;
        r.x = this->x / value;
        r.y = this->y / value;
        return r;
    }
    template<class X, class Y>
    Point operator()(const X& x, const Y& y)
    { 
        this->x = x;
        this->y = y;
        return *this;
    }
};

inline Point<float> operator*(float value, Point<float> v)
{
    return v * value;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class catmullrom
{
    public:
        Point<float>* p;
        Point<float>* v;
        const int points;

        catmullrom(const int segments): points(segments)
        {
            p = new Point<float>[points];
            v = new Point<float>[points];
        }
       ~catmullrom()
        {
            delete v;
            delete p;
        }


    Point<float> getft(float time)
    {
        Point<float> ret;
        int n = points-1;
        int i = (int)time;
        float t = time - i;
        if(i == n)
        {
            ret = (2*p[i]-2*p[0]+v[i]+v[0])*t*t*t
                + (-3*p[i]+3*p[0]-2*v[i]-v[0])*t*t
                + v[i]*t
                + p[i];
        }
        else
        {
            ret = (2*p[i]-2*p[i+1]+v[i]+v[i+1])*t*t*t
                + (-3*p[i]+3*p[i+1]-2*v[i]-v[i+1])*t*t
                + v[i]*t
                + p[i];
        }
        return ret;
    }

    void calcv()
    {
        Point<float> temp;

        temp = (p[1]-p[0])*2-(p[2]-p[0])/2;
        v[0] = temp;
        for(int i = 1; i < points-1; i++)
        {
            temp = (p[i+1]-p[i-1])/2;
            v[i] = temp;
        }
        temp = (p[points-1]-p[points-2])*2-(p[points-1]-p[points-2])/2;
        v[points-1] = temp;
    }
};

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
inline point2d<float> interpolatedPosition(point2d<float> p0, point2d<float> p1, point2d<float> p2, point2d<float> p3, float t)
{
    float t3 = t * t * t;
    float t2 = t * t;

    float f1 = -0.5 * t3 + t2 - 0.5 * t;
    float f2 =  1.5 * t3 - 2.5 * t2 + 1.0;
    float f3 = -1.5 * t3 + 2.0 * t2 + 0.5 * t;
    float f4 =  0.5 * t3 - 0.5 * t2;

    float x = p0.x * f1 + p1.x * f2 + p2.x * f3 + p3.x * f4;
    float y = p0.y * f1 + p1.y * f2 + p2.y * f3 + p3.y * f4;

    return point2d<float>{x, y};
}


inline point2d<float> interpolateBezier(point2d<float> p0, point2d<float> p1, point2d<float> p2, point2d<float> p3, float t) // t always lies between 0 and 1
{
    float x, y;
    x = pow(1-t, 3) * p0.x + 3*t*pow(1-t,2) * p1.x + 3*t*t*(1-t) * p2.x + pow(t,3) * p3.x; // Formula to draw curve
    y = pow(1-t, 3) * p0.y + 3*t*pow(1-t,2) * p1.y + 3*t*t*(1-t) * p2.y + pow(t,3) * p3.y;
    return point2d<float>{x, y};
}



};