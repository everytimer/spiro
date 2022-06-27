//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "NumberBox.h"
#include "Interface.h"
#include "Socket.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GribAudioProcessorEditor  : public juce::AudioProcessorEditor , public juce::Timer//, public juce::MidiInputCallback
{
    public:
        uint WIDTH  = 640;
        uint HEIGHT = 480;
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
        NumberBox nbCoarse;
        NumberBox nbVolume;
        NumberBox nbDetune;
        NumberBox nbWarp;
        NumberBox nbAmp;  
        
        NumberBox nbH1;        
        NumberBox nbH2;    
        NumberBox nbH3;    
        NumberBox nbH4;    
        NumberBox nbH5;    
        NumberBox nbH6;    
        NumberBox nbH7;    
        NumberBox nbH8;    
        // juce::Slider sliderKnob {juce::Slider::SliderStyle::Rotary, juce::Slider::TextBoxAbove};


               
        Sockets SC {20, 180, 300, 200, 10};
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GribAudioProcessorEditor)
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////