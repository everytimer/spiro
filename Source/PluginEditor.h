//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "NumberBox.h"
#include "InfSlider.h"
#include "fSlider.h"
#include "SpriteSlider.h"
#include "Socket.h"
#include "Operator.h"
#include "EnvelopeDisplay.h"
#include "ListSlider.h"
#include "lists.hpp"
#include "serpent/spectrum.hpp"
#include "serpent/blur.hpp"
#include "serpent/primitives.hpp"
#include "serpent/sdfaabb.hpp"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GribAudioProcessorEditor: public juce::AudioProcessorEditor , public juce::Timer//, public juce::MidiInputCallback
{
    public:
        uint WIDTH  = 1000;
        uint HEIGHT = 562;
        juce::Rectangle<int> rWaveDisplay;
        juce::Rectangle<int> rSpiroDisplay;
        juce::Rectangle<int> rSpectreDisplay;


        void WaveDisplay (juce::Graphics&, float);
        void SpectralDisplay (juce::Graphics&, float);
        void SpiroDisplay(juce::Graphics&, float, int);

        EnvelopeDisplay eds;
        
        cell::frame<float>* spCanvas;
        cell::frame<float>* wdCanvas;
        cell::frame<float>* sdCanvas;

        // cell::spectre spectrum {128, 48000};

        //cell::wavering<float> buffer;
        void paint (juce::Graphics&) override;
        void resized() override;
        void timerCallback() override { repaint(rWaveDisplay); repaint(rSpiroDisplay); };

        GribAudioProcessorEditor (GribAudioProcessor&);
       ~GribAudioProcessorEditor() override;

    private:

        GribAudioProcessor& audioProcessor;

        Rot3Slider spdXYZ;
        Operator operator_a;
        Operator operator_b;
        Operator operator_c;
        Operator operator_d;
        Operator operator_e;
        Operator operator_f;

        ListSlider form_a;
        ListSlider form_b;
        ListSlider form_c;
        ListSlider form_d;
        ListSlider form_e;
        ListSlider form_f;

        fSlider   wdVolume;
              
        Sockets SC { 512, 192, 40 };
        // SpriteSlider SS;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GribAudioProcessorEditor)
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////