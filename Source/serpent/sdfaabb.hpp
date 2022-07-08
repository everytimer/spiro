/////////////////////////////////////////////////////////////////////////////////////
// https://github.com/miloyip/line/blob/master/line_sdfaabb.c ///////////////////////
// Signed distnace field (SDF) optimization with AABB ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cmath>  
#include "containers.hpp"

namespace cell {

float capsule_sdf(float px, float py, float ax, float ay, float bx, float by, float r) 
{
    float pax = px - ax, pay = py - ay, bax = bx - ax, bay = by - ay;
    float h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    float dx = pax - bax * h, dy = pay - bay * h;
    return sqrtf(dx * dx + dy * dy) - r;
}

void alphablend(cell::frame<float>* canvas, int x, int y, float alpha) 
{
    auto a = canvas->get(x, y);
    canvas->set(x, y, a * (1.0f - alpha) + alpha);
}

void lineSDFAABB(cell::frame<float>* canvas, float ax, float ay, float bx, float by, float radius, float alpha) 
{
    int x0 = (int)floorf(fminf(ax, bx) - radius);
    int x1 = (int) ceilf(fmaxf(ax, bx) + radius);
    int y0 = (int)floorf(fminf(ay, by) - radius);
    int y1 = (int) ceilf(fmaxf(ay, by) + radius);
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            alphablend(canvas, x, y, fmaxf(fminf(0.5f - capsule_sdf(x, y, ax, ay, bx, by, radius), 1.0f), alpha));
}
};