#pragma once
#include <JuceHeader.h>
#include <iostream>
#include "Colours.hpp"
#include "serpent/blur.hpp"
#include "serpent/envelopes.h"
#include "serpent/primitives.hpp"
#include "serpent/containers.hpp"
#include "ListSlider.h"
#include "NumberBox.h"
#include "RadioButton.h"
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
class EnvelopeDisplay  : public juce::Component
{
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeDisplay)
    public:
        float radius = 6;
        float diameter = radius*2;

        float aA = 0.15f, rR = 0.7f; 
        cell::envelope env;
        cell::frame<float>*  canvas;
        juce::Rectangle<int> area;
        juce::Rectangle<int> display;

        int radio_id = 0xFA;

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
            int x,  y;
            int cl, cr; // Left/Right constrain
            int ct, cb; // Top/Bottom constrain

            void paint (juce::Graphics& g) override
            {
                auto bounds = getLocalBounds();

                g.setColour (colour_set[4].withAlpha (0.5f));
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

                if(x>=cr) setCentrePosition(x=cr, y);
                if(x<=cl) setCentrePosition(x=cl, y);
                if(y>=cb) setCentrePosition(x, y=cb);

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

        RadioButton ENV_A;
        RadioButton ENV_B;
        RadioButton ENV_C;
        RadioButton ENV_D;
        RadioButton ENV_E;
        RadioButton ENV_F;
        // void mouseUp (const juce::MouseEvent&) override;
        // void mouseDrag (const juce::MouseEvent&) override;
        void mouseDown(const juce::MouseEvent&) override;

        EnvelopeDisplay ();
       ~EnvelopeDisplay() override;
};
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////