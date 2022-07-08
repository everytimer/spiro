#pragma once
#include <JuceHeader.h>
#include <iostream>
#include "Colours.hpp"
#include "serpent/blur.hpp"
#include "serpent/envelopes.h"
#include "serpent/primitives.hpp"
#include "serpent/containers.hpp"
#include "NumberBox.h"
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class EnvelopeDisplay  : public juce::Component
{
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeDisplay)
    public:
        float diameter = 14;

        NumberBox A;
        NumberBox R;
        float aA = 0.05f, rR = 0.5f; 
        cell::envelope env;
        cell::frame<float>*  canvas;
        juce::Rectangle<int> area;
        juce::Rectangle<int> display;



        void plot(juce::Graphics& g, float scale);

        void updateNodes();
        void paint (juce::Graphics& g) override;
        void resized() override;
        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        struct  NodePoint : public juce::Component
        {
            juce::ComponentDragger node;
            juce::ComponentBoundsConstrainer constrainer;
            EnvelopeDisplay* parent;
            int x, y;

            void paint (juce::Graphics& g) override
            {
                auto bounds = getLocalBounds().reduced  (1);
                auto blue = juce::Colour::fromFloatRGBA (0.42f, 0.83f, 1.0f,  0.7f);

                g.setColour (blue.withAlpha (0.5f));
                g.fillEllipse (bounds.toFloat());
            }

            void mouseDown (const juce::MouseEvent& event) override
            {
                node.startDraggingComponent (this, event);
            }

            void mouseDrag (const juce::MouseEvent& event) override
            {
                node.dragComponent (this, event, &constrainer);
                x = getX() + getWidth ()/2;
                y = getY() + getHeight()/2;
                parent->repaint();
            }

            NodePoint(EnvelopeDisplay* p): parent(p)
            {
                auto d = parent->diameter;
                constrainer.setMinimumOnscreenAmounts (d, d, d, d);
            }

            void resized() override
            {
                x = getX() + getWidth() /2;
                y = getY() + getHeight()/2;
                parent->repaint();
            }
        };
        ///////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////// 
        NodePoint npa;
        NodePoint npd;
        NodePoint nps;
        NodePoint npr;

        EnvelopeDisplay ();
       ~EnvelopeDisplay() override;
};
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////