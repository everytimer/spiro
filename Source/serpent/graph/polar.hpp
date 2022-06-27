#pragma once
#include<cmath>

struct WaveSeries
{
    const int   nharm = 1;
    const float tao = M_PI*2.0f;
    float*      radius;
    float*      theta;
    float       delta = 0.0001f;
    float       x, y, z;

    void polar();
    void process();
    WaveSeries(const int);
    WaveSeries();
   ~WaveSeries();
};

WaveSeries::WaveSeries(const int size): nharm(size)
{
    radius = new float[nharm];
    theta  = new float[nharm];
}

WaveSeries::WaveSeries()
{
    radius = new float[nharm];
    theta  = new float[nharm];
}

WaveSeries::~WaveSeries()
{
    delete theta;
    delete radius;
}

void WaveSeries::polar()
{
    // radius = sqrtf(x * x + y * y);
    // theta  = atanf(y / x) * (180.0f / M_PI);
}
    
void WaveSeries::process()
{
    x = 0;
    y = 0;
    for(int i = 0; i < nharm; i++)
    {
        x += radius[i] * cos(theta[i]); 
        y += radius[i] * sin(theta[i]);
    }
}


void square_wave(WaveSeries *W, const float r)
{
    static float angle;
    for(int i=0; i < W->nharm; i++)
    {
        W->theta[i] = angle * (i*2 + 1);
        W->radius[i] = r / (i*2 + 1);
    }
    W->process();
    angle += W->delta;
    if(angle>(M_PI*2)) angle = 0.0f;
}