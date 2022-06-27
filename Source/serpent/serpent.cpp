////////////////////////////////////////////////////////////////////////////////////////
// SERPENT - Algorhithmic sequencer
// V.0.0.1 2022-01-14
////////////////////////////////////////////////////////////////////////////////////////

#include "serpent.h"

namespace cell {

void serpent::init()
{
        in=0; is=0;
        note = sequence.at(in);
        step = timeline.at(is);
        //offset = *departed; //<-segmentation fault // prev: clock()
}

void serpent::next()
{       
        in==sequence.size()-1? in=0: in++;
        if(is==timeline.size()-1) is=0;
        else is++;
        note = sequence.at(in);
        step = timeline.at(is); 
        offset= *departed;    
}

void serpent::prior()
{       
        in==0? in=sequence.size()-1: in--;
        if(is==0)  is=timeline.size()-1;  
        else is--;
        note = sequence.at(in);
        step = timeline.at(is);
        offset= *departed;
}

// Set scale by the string input
void serpent::set(const string& s)
{
        scale = string_to_hz(s,A4);
        sequence = scale;
        init();
}
// #include <iostream>
////////////////////////////////////////////////////////////////////////////////////////
// Time    = full pattern length in ms
// Pattern = bit representation of rhythm : 0b1000100010001000
////////////////////////////////////////////////////////////////////////////////////////
void serpent::timeset(const float& t)
{
        timeline = {};
        uint bset = pattern;
        uint mask = 1; mask<<=(steps-1);
        float step = t/steps;
        float acc = 0;
        for(int i=0;i<steps;i++)
        {
            if((bset&mask)==0) acc+=step;
            else { timeline.push_back(acc); acc=step; }
            bset<<=1;
        }
        timeline.push_back(acc);
        init();
}

// Index = function type
void serpent::regenerate(uint index)
{
        sequence = fF[index](scale.size(), seed[0], octaves, scale);
}

serpent::serpent(const string& s, uint time, const uint& p): pattern(p)
{
        timeline.reserve(100);
        scale = string_to_hz(s,A4);
        sequence = scale;
        timeset(time);
        init();
}

serpent::~serpent()
{
}

////////////////////////////////////////////////////////////////////////////////////////
// Vector <bool> to Uint32 /////////////////////////////////////////////////////////////
uint vector_to_int(const vector<bool>& v)
{
        uint r(0);
        for(size_t i=0; i<v.size(); i++)
        {
                r+=v[i];
                if(i!=v.size()-1) r<<=1;
        }
        return r;
}

////////////////////////////////////////////////////////////////////////////////////////
// Uint32 ot Vector <bool> /////////////////////////////////////////////////////////////
vector<bool> int_to_vector(const uint& f)
{
        vector<bool> r(32,0);
        uint e = f; int i = 31;
        while(e)
        {
                r[i] = e&1;
                i--;
                e>>=1;
        }
        return r;
}

////////////////////////////////////////////////////////////////////////////////////////
// Beat divider ////////////////////////////////////////////////////////////////////////
// Where f is bit representation of rhythm of 32 bit width, d is divisor
uint beat_divide(const uint& f, const int& d)
{
        if(d==2)
        {
                uint mask = 0xFFFF; 
                uint s = f&mask;
                uint r = s;
                r<<=16; r+= s;
                return r;
        }
        else if(d==4)
        {
                uint mask = 0xFF; 
                uint s = f&mask;
                uint r = s;
                r<<=8; r+= s;
                r<<=8; r+= s;
                r<<=8; r+= s;
                return r;
        }
        return f;
}

////////////////////////////////////////////////////////////////////////////////////////
// Collatz /////////////////////////////////////////////////////////////////////////////
vector<float> fsC3N1(uint n, uint seed, uint octaves, const vector<float>& scale)
{
        vector<uint> esq(n,0); uint i=0;
        while (i<n)
        {
                seed = (seed & 1)? 3 * seed + 1 : seed / 2;
                esq[i] = (seed % (scale.size()*octaves));
                i++;
        }
        vector<float> sq {};
        for(auto e: esq) { sq.push_back(scale.at(e%scale.size())*(e/scale.size()+1)); }
        return sq;
}

uint frC3N1(uint seed)
{       uint r = (seed & 1)? 3 * seed + 1 : seed / 2;
        r*=100;
        return r<3? 3: r;
}




vector<float> fsLorenz(uint n, uint seed, uint octaves, const vector<float>& scale)
{
        static lorenz la;
        vector<uint> esq(n,0); uint i=0;
        uint r;
        //la.a=seed%100;
        
        while (i<n)
        {
                la.iterate();
                r = fabs(la.x*la.y*la.z); //*seed;
                esq[i] = (r % (scale.size()*octaves));
                i++;
        }
        vector<float> sq {};
        for(auto e: esq) { sq.push_back(scale.at(e%scale.size())*(e/scale.size()+1)); }
        return sq;
}

uint frLorenz(uint seed)
{
        static lorenz la;
        la.iterate();
        uint r = uint(la.x*10000);
        return r<3? 3: r;
}


vector<float> fsLangtons(uint n, uint seed, uint octaves, const vector<float>& scale)
{
        static langtons_ant la;
        vector<uint> esq(n,0); uint i=0;
        uint r;


        vector<float> sq {};
        for(auto e: esq) { sq.push_back(scale.at(e%scale.size())*(e/scale.size()+1)); }
        return sq;
}



uint frLangtons(uint seed)
{
        static langtons_ant lant;
        lant.move();
        static uint r = 0;
        for(int i = 0; i< 32; i++)
        {
                r += lant.field[i];
                if(i != 31) r <<= 1;
        }
        return r;

}
};