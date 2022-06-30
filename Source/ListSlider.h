#pragma once

#include <JuceHeader.h>

class ListSlider  : public juce::Slider
{
    public:

        void paint (juce::Graphics& g) override;
        void mouseDown (const juce::MouseEvent& event) override;
        void mouseUp (const juce::MouseEvent& event) override;
        ListSlider();
       ~ListSlider();
};
