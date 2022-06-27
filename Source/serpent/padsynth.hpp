// PADsynth implementation as ready-to-use C++ class.
// By: Nasca O. Paul, Tg. Mures, Romania

#pragma once
#include <cmath>
#include "constants.hpp"



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../fftwrapper/FFTwrapper.h"

/* Random number generator */
float RND()
{
    return (rand() / (RAND_MAX + 1.0f));
};

// This is the profile of one harmonic
// In this case is a Gaussian distribution (e^(-x^2))
// The amplitude is divided by the bandwidth to ensure that the harmonic
// keeps the same amplitude regardless of the bandwidth 
float profile(float fi,float bwi)
{
    float x = fi / bwi;
    x *= x;
    if (x > 14.71280603) return 0.0; // this avoids computing the e^(-x^2) where it's results are very close to zero
    return exp(-x) / bwi;
};


// Inverse Fast Fourier Transform
// You may replace it with any IFFT routine
void IFFT(int N, float *freq_amp, float *freq_phase, float *smp)
{
    FFTwrapper fft(N);
    FFTFREQS fftfreqs;
    newFFTFREQS(&fftfreqs, N/2);

    for (int i = 0; i < N/2; i++)
	{
		fftfreqs.c[i] = freq_amp[i] * cos(freq_phase[i]);
		fftfreqs.s[i] = freq_amp[i] * sin(freq_phase[i]);
    }
    fft.freqs2smps(fftfreqs, smp);
    deleteFFTFREQS(&fftfreqs);
};


// Simple normalization function. It normalizes the sound to 1/sqrt(2)
void normalize(int N,float *smp)
{
    int i;
    float max = 0.0;
    for (i = 0; i < N; i++) if (fabs(smp[i]) > max) max = fabs(smp[i]);
    if  (max < 1e-5) max = 1e-5;
    for (i = 0; i < N; i++) smp[i] /= max * 1.4142f;
}


// The relF function returns the relative frequency of the N'th harmonic
// to the fundamental frequency.
float relF(int N)
{
    return (N * (1.0f + N * 0.1f));
}


// This is the implementation of PADsynth algorithm.
void padsynth_extended_algorithm(int N,	int samplerate,	float f, float bw, float bwscale, int nharm, float *A, float *smp)
{
    int i, nh;
    float *freq_amp = new float[N/2];
    float *freq_phase = new float[N/2];
    
    for (i = 0; i < N/2; i++) freq_amp[i] = 0.0f; //default, all the frequency amplitudes are zero

    for (nh = 1; nh < nharm; nh++) // for each harmonic
	{
		float bw_Hz; //bandwidth of the current harmonic measured in Hz
        float bwi;
		float fi;
        bw_Hz = (pow(2.0f, bw / 1200.0f) - 1.0f) * f * pow(relF(nh), bwscale);
	
		bwi = bw_Hz / (2.0f * samplerate);
		fi = f * relF(nh) / samplerate;
		for (i = 0; i < N / 2; i++)
		{
	    	float hprofile;
	    	hprofile = profile((i / (float)N) - fi, bwi);
	    	freq_amp[i] += hprofile * A[nh];
		}
    }
    //Add random phases
    for (i = 0; i < N / 2; i++)
	{
		freq_phase[i] = RND() * TAO;
    };
    
    IFFT(N, freq_amp, freq_phase, smp);
    normalize(N, smp);
    
    delete [] freq_amp;
    delete [] freq_phase;
};

#define N (262144)
float sample[N];

#define nharm 64
int padProcess()
{
    srandom(time(0));
    float A[nharm];A[0]=0.0;//A[0] is not used
    for (int i=1;i<nharm;i++) A[i]=1.0/i;
    padsynth_extended_algorithm(N, 44100, 261.0, 20.0, 0.5, nharm, A, sample);

    /* Output the data to the 16 bit, mono raw file */
    short int isample[N];
    for (int i=0;i<N;i++) isample[i]=(int)(sample[i]*32768.0);
    FILE *f=fopen("sample.raw","w");fwrite(isample,N,2,f);fclose(f);
}