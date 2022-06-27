////////////////////////////////////////////////////////////////////////////////////////
// COLOUR MORPH FUNCTIONS
// v.0.0.1
// 32bit Format
// 3-01-2022
////////////////////////////////////////////////////////////////////////////////////////


#ifndef MORPH_FUNCTIONS
#define MORPH_FUNCTIONS
#include <cstdlib>
#include "frame.hpp"

void fADD(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)+B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fSUB(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)-B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fMUL(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)*B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fXOR(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)^B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fOR(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)|B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fAND(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)&B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fRSHIFT(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)>>B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void fLSHIFT(Frame* A, Frame* B){
    uint W= A->width;
    uint H= A->heigth;
    uint colour= 0;
    for(uint x= 0; x<W; x++){
        for(uint y= 0; y<H; y++){
            colour= A->at(x,y)<<B->at(x,y);
            A->pset(x,y,colour);
        }
    }
}

void (*morph[])(Frame*, Frame*)={ fADD,
                                    fSUB,
                                    fMUL,
                                    fXOR,
                                    fOR,
                                    fAND,
                                    fRSHIFT,
                                    fLSHIFT };





#endif