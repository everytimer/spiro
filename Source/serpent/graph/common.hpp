#ifndef __COMMON
#define __COMMON

#define mask_r 0xFF000000
#define mask_g 0x00FF0000
#define mask_b 0x0000FF00
#define mask_a 0x000000FF


#include <utility>
#include <cmath>
using std::pair;


pair<double, double> shear(double theta, double x, double y)
{
    pair<double, double> res; 
    double t    = tan  (theta/2);
    res.first   = round(x-y*t);
    res.second  = y;
    res.second  = round(res.first*sin(theta)+res.second);      
    res.first   = round(res.first-res.second*t);              
    return res;
}



#endif