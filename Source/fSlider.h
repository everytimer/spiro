#pragma once
#include <JuceHeader.h>

class fSlider  : public juce::Slider
{
    public:
        float mod = 0.0f; // -1:1
        float eax;
        float range;
        float centre;
        void paint (juce::Graphics& g) override;
        void mouseDown (const juce::MouseEvent& event) override;
        void mouseUp (const juce::MouseEvent& event) override;
        fSlider();
       ~fSlider();
};
