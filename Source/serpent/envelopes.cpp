////////////////////////////////////////////////////////////////////////////////////////
// ENVELOPES
// V.0.3.6 2022-02-19
////////////////////////////////////////////////////////////////////////////////////////
#include "envelopes.h"
namespace cell {

void envelope::start()
{
    init();
    delta = node[stage].value;

}

void envelope::init()
{
    stage    = 0;
    departed = 0;
    node[0].value = 0.0f;
    node[0].time  = 0.0f;
    // node[segments-1].value = 0.0f;
    // node[segments-1].time  = 0.0f;
}

void envelope::next_stage()
{
    stage++;
    departed = 0;

    if  (stage >= segments)  stage = -1;
    else delta = node[stage].value - node[stage-1].value;
}

float envelope::iterate()
{
    if(stage>=0)
    {
    feed = formEnvelope[node[stage].curve](float(departed), node[stage-1].value, delta, node[stage].time);
    departed++;
    if(departed > node[stage].time) next_stage();
    }
    return feed;
}



cell::envelope::envelope()
{
    node = new breakpoint[segments];
    init();
}

cell::envelope::~envelope()
{
    delete[] node;
}


////////////////////////////////////////////////////////////////////////////////////////////
// t = Time - Amount of time that has passed since the beginning.
// b = Beginning value - The starting point of the transition.
// c = Change in value - The amount of change needed to go from starting point to end point.
// d = Duration - Amount of time the transition will take.
////////////////////////////////////////////////////////////////////////////////////////////
float fLinear(float t, float b, float c, float d)
{
        return c * t / d + b;
}
////////////////////////////////////////////////////////////////////////////////////////////
float fCubicIn(float t, float b, float c, float d)
{
        t /= d;
	    return c*t*t*t + b;
}
////////////////////////////////////////////////////////////////////////////////////////////
float fCubicOut(float t, float b, float c, float d)
{
        t /= d;
        t--;
        return c * (t*t*t + 1.0f) + b;
};
////////////////////////////////////////////////////////////////////////////////////////////
float fCubicIO(float t, float b, float c, float d)
{
        t /= (d * 0.5f);
        if (t < 1.0f) return c * 0.5f * t*t*t + b;
        t -= 2;
        return c * 0.5f * (t*t*t + 2.0f) + b;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


// float envelope::coefficient(float start_value, float end_value, uint length) 
// {
//         if(curve==LIN) return (end_value-start_value)/float(length);
//         if(curve==LOG) return (log(end_value)-log(start_value))/float(length);
//         return 1;
// }


// vector<float> imprint(cell::envelope *node, int offset_left, int offset_right)
// {
//     float w =   node->node.A.time + 
//                 node->node.D.time + 
//                 node->node.S.time + 
//                 node->node.R.time ;
//     std::vector<float> r(offset_left,0);
//                 node->start();
//                 int i = 0;
            
//                 while (i<int(w))
//                 {
//                     r.push_back(node->iterate()); 
//                     i++; 
//                 }
//                 i=0;
//                 while (i<offset_right)
//                 {
//                     r.push_back(0); i++;
//                 }
                
//     return r;
// }

};