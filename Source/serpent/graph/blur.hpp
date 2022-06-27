#include <cstdlib>
#include "colour_functions.hpp"
#include "cvframe.hpp"

void blur(const cvframe* data, uint scale, cvframe *out){
    
    RGBA acc= {0,0,0,0};
    RGBA car;
    // for(uint y= 0; y< data->heigth; y++)
    // {
    //     for(uint x= 0; x< data->width; x++)
    //     {
    //         for(int i= 0; i<scale; i++)
    //         {   
    //             car = GET_RGBA(data->at(x+i,y));
    //             acc.R+= car.R;
    //             acc.G+= car.G;
    //             acc.B+= car.B;
    //         }
    //         acc.R/=scale;
    //         acc.G/=scale;
    //         acc.B/=scale;
    //         out->pset(x,y, SET_RGBA(acc));
    //         acc={0,0,0,0};
    //     }
    // }

    for(uint x= 0; x< data->width; x++)
    {
        for(uint y= 0; y< data->heigth-scale; y++)
        {
            for(int i= 0; i<scale; i++)
            {   
                car = GET_RGBA(data->at(x,y+i));
                acc.R+= car.R;
                acc.G+= car.G;
                acc.B+= car.B;
            }
            acc.R/=scale;
            acc.G/=scale;
            acc.B/=scale;

            out->pset(x,y, SET_RGBA(acc));
            acc={0,0,0,0};
        }
    }

}