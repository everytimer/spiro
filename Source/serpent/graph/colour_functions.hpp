#ifndef COLOUR_FUNCTIONS
#define COLOUR_FUNCTIONS

#include <cstdlib>
#include "common.hpp"

struct RGBA{
    uint R;
    uint G;
    uint B;
    uint A;
};

uint SET_RGBA(uint r, uint g, uint b, uint a);
uint SET_ARGB(uint a, uint r, uint g, uint b);
uint SET_ABGR(uint a, uint b, uint g, uint r);

uint SET_RGBA(RGBA);

RGBA GET_RGBA(uint);
RGBA GET_ARGB(uint);
RGBA GET_ABGR(uint);


uint SET_ALPHA(uint colour, uint alpha)
{
    RGBA C = GET_RGBA(colour);
    C.A = alpha;
    return SET_RGBA(C);
}


uint SET_RGBA(uint r= 0, uint g= 0, uint b= 0, uint a= 0){
    uint res= 0;
    res += r; res <<= 8;
    res += g; res <<= 8;
    res += b; res <<= 8;
    res += a;
    return res;
}

uint SET_ARGB(uint a= 0, uint r= 0, uint g= 0, uint b= 0){
    uint res= 0;
    res += a; res <<= 8;
    res += r; res <<= 8;
    res += g; res <<= 8;
    res += b;
    return res;
}

uint SET_ABGR(uint a= 0, uint b= 0, uint g= 0, uint r= 0){
    uint res= 0;
    res += a; res <<= 8;
    res += b; res <<= 8;
    res += g; res <<= 8;
    res += r;
    return res;
}

uint SET_RGBA(RGBA c){
    uint res= 0;
    res += c.R; res <<= 8;
    res += c.G; res <<= 8;
    res += c.B; res <<= 8;
    res += c.A;
    return res;
}

RGBA GET_RGBA(uint colour){
    RGBA res;
    res.R      = (colour&mask_r); res.R>>=24;
    res.G      = (colour&mask_g); res.G>>=16;
    res.B      = (colour&mask_b); res.B>>= 8;
    res.A      = (colour&mask_a);
    return res;
}


uint DIM_COLOUR(uint colour, float factor)
{
    if(factor > 1.0f) return colour;
    if(factor < 0.0f) return 0;

    RGBA C = GET_RGBA(colour);

    C.R = float(C.R) * factor;
    C.G = float(C.G) * factor;
    C.B = float(C.B) * factor;
    C.A = float(C.A) * factor;

    return SET_RGBA(C);
}

uint DIM_ALPHA(uint colour, float factor)
{
    if(factor > 1.0f) return colour;
    if(factor < 0.0f) return 0;

    RGBA C = GET_RGBA(colour);

    C.A = float(C.A) * factor;

    return SET_RGBA(C);
}

uint ADD(uint colour_a, uint colour_b)
{
    RGBA CA = GET_RGBA(colour_a);
    RGBA CB = GET_RGBA(colour_b);

    float f = (float)CB.A/255.0f;

    CA.R += (float)CB.R * f; 
    if (CA.R > 0xFF) CA.R = 0xFF;
    CA.G += (float)CB.G * f; 
    if (CA.G > 0xFF) CA.G = 0xFF;
    CA.B += (float)CB.B * f; 
    if (CA.B > 0xFF) CA.B = 0xFF;

    return SET_RGBA(CA);
}

#endif