#pragma once

#include <JuceHeader.h>

class NumberBox  : public juce::Slider
{
    public:
        float mod = 0.0f; // -1:1
        float eax;
        float range;
        float centre;
        // juce::Colour normalColour;
        // juce::Colour hoveredColour;

        void paint (juce::Graphics& g) override;
        void mouseDown (const juce::MouseEvent& event) override;
        void mouseUp (const juce::MouseEvent& event) override;
        // void mouseEnter (const juce::MouseEvent& event) override;
        // void mouseExit (const juce::MouseEvent& event) override;
        NumberBox();
       ~NumberBox();
};
