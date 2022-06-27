/*
  ==============================================================================
    NumberBox.h
    Created: 8 Aug 2021 7:46:08am
    Author:  Kengo Suzuki
    https://github.com/szkkng/numberbox/blob/main/Source/NumberBox.h
    https://suzuki-kengo.dev/posts/numberbox
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NumberBox  : public juce::Slider
{
    public:
        float mod = 0.0f; // -1:1
        float eax;
        float range;
        float centre;
        void paint (juce::Graphics& g) override;
        void mouseDown (const juce::MouseEvent& event) override;
        void mouseUp (const juce::MouseEvent& event) override;
        NumberBox();
       ~NumberBox();
};
