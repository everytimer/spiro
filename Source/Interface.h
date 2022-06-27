#pragma once
#include <JuceHeader.h>


class Interface : public juce::LookAndFeel_V4
{
public:
    Interface()
    {   
        imageKnob = juce::ImageCache::getFromMemory(BinaryData::Knob_C01_png, BinaryData::Knob_C01_pngSize);
    }

    void drawRotarySlider(juce::Graphics&, int, int, int, int, float, float, float, juce::Slider&);
    juce::Image imageKnob;
    
};

