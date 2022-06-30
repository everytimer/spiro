//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "NumberBox.h"
#include "InfSlider.h"
#include "fSlider.h"
#include "Interface.h"
#include "Socket.h"
#include "Operator.h"
#include "serpent/spectrum.hpp"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GribAudioProcessorEditor  : public juce::AudioProcessorEditor , public juce::Timer//, public juce::MidiInputCallback
{
    public:
        uint WIDTH  = 900;
        uint HEIGHT = 506;
        juce::Rectangle<int> rWaveDisplay;
        juce::Rectangle<int> rSpiroDisplay;

        void WaveDisplay (juce::Graphics&, float);
        void SpectralDisplay (juce::Graphics&, float);
        void SpiroDisplay(juce::Graphics&, float, int);
        cell::frame<float>* spCanvas;
        cell::frame<float>* wdCanvas;

        // cell::spectre spectrum {128, 48000};

        //cell::wavering<float> buffer;
        void paint (juce::Graphics&) override;
        void resized() override;
        void timerCallback() override { repaint(rWaveDisplay); repaint(rSpiroDisplay); };

        GribAudioProcessorEditor (GribAudioProcessor&);
       ~GribAudioProcessorEditor() override;

    private:
        Interface interface;

        GribAudioProcessor& audioProcessor;
        InfSlider spRotateX;
        InfSlider spRotateY;
        InfSlider spRotateZ;
       
        Operator operator_a;
        Operator operator_b;
        Operator operator_c;
        Operator operator_d;

        fSlider   wdVolume;
              
        Sockets SC { 512, 192, 40 };
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GribAudioProcessorEditor)
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////