#pragma once
#include <JuceHeader.h>
#include "serpent/containers.hpp"
#include "serpent/primitives.hpp"
#include "Colours.hpp"
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

class Rot3Slider: public juce::Component
{
    private:
    public:
        InfSlider X;
        InfSlider Y;
        InfSlider Z;

        juce::Colour outline;
        juce::Colour background;

        juce::Rectangle<int> area;
        void drawSBrace(juce::Graphics&, float, float, float, float, float, float);
        void paint (juce::Graphics& g) override;
        void resized () override;
        Rot3Slider();
       ~Rot3Slider();
};


