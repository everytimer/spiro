#pragma once
#include "Colours.hpp"
#include <JuceHeader.h>

class RadioButton  : public juce::ToggleButton
{
    public:
        juce::Rectangle<int> area;
        void paint (juce::Graphics& g) override;
        // void mouseDown (const juce::MouseEvent& event) override;
        // void mouseUp (const juce::MouseEvent& event) override;
        void resized() override;

        // void mouseEnter (const juce::MouseEvent& event) override;
        // void mouseExit (const juce::MouseEvent& event) override;
        RadioButton();
       ~RadioButton();
};
