#pragma once

#include <JuceHeader.h>
#include <vector>
#include "NumberBox.h"
#include "Colours.hpp"

class Operator: public juce::Component
{
    private:
    public:
        juce::Rectangle<int>    area;
        juce::Rectangle<int>    t_area;

        NumberBox coarse;   // Octave
        NumberBox fine;     // Detune
        NumberBox theta;    // Latitude
        NumberBox fm;       // Frequency modulation
        NumberBox warp;     // Waveform dependent modulation
        NumberBox amp;      // Amplitude

        void resized () override;
        void paint (juce::Graphics& g) override;
        Operator();
       ~Operator();
};