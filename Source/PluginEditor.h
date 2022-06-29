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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GribAudioProcessorEditor  : public juce::AudioProcessorEditor , public juce::Timer//, public juce::MidiInputCallback
{
    public:
        uint WIDTH  = 900;
        uint HEIGHT = 506;
        juce::Rectangle<int> rWaveDisplay;
        juce::Rectangle<int> rSpiroDisplay;

        void WaveDisplay (juce::Graphics&, float);
        void SpiroDisplay(juce::Graphics&, float, int);
        cell::frame<float>* spCanvas;
        cell::frame<float>* wdCanvas;

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
       

        NumberBox nbCoarse;
        NumberBox nbDetune;
        NumberBox nbTheta;
        NumberBox nbAmp; 
        NumberBox nbPwm;
        NumberBox nbFm;

        NumberBox nbWarp;
         
        juce::Label fmLabel;
        fSlider   wdVolume;

        // juce::Slider sliderKnob {juce::Slider::SliderStyle::Rotary, juce::Slider::TextBoxAbove};


               
        Sockets SC {20, 180, 300, 200, 10};
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GribAudioProcessorEditor)
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////