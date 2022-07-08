#pragma once

#include <JuceHeader.h>
#include <vector>
#include "serpent/modmatrix.hpp"
#include "Colours.hpp"

class Sockets: public juce::Component
{
    private:
    public:
        cell::patchbay* bay;
        juce::Rectangle<int>    area;
        bool  drag    = false;
        float opacity = 0.8f;
        int   route   = -1;
        bool  i_armed = false;
        bool  o_armed = false;

        void drawIns(juce::Graphics&, juce::Colour, int);
        void drawOuts(juce::Graphics&, juce::Colour, int);

        void drawSockets(juce::Graphics&, juce::Colour);
        void drawCords(juce::Graphics&, float);
        void mouseUp (const juce::MouseEvent&) override;
        void mouseDrag (const juce::MouseEvent&) override;
        void mouseDown(const juce::MouseEvent&) override;
        void resized () override;
        void paint (juce::Graphics& g) override;
        Sockets(int, int, int);
       ~Sockets();
};