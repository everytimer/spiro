#pragma once
#include <JuceHeader.h>
#include "serpent/containers.hpp"
#include "serpent/primitives.hpp"
#include "serpent/blur.hpp"

class InfSlider  : public juce::Slider
{
    public:

        void paint (juce::Graphics& g) override;
        void mouseDown (const juce::MouseEvent& event) override;
        void mouseUp (const juce::MouseEvent& event) override;
        InfSlider();
       ~InfSlider();
};
