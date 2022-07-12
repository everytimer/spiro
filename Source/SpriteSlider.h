#pragma once
#include <JuceHeader.h>


class SpriteSlider : public juce::Slider
{
    public:
        void paint (juce::Graphics& g) override;
        juce::Image imageKnob;
        SpriteSlider();
};