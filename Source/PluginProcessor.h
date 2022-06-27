//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <JuceHeader.h>
#include "serpent/feeder.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GribAudioProcessor  : public juce::AudioProcessor
{
    public:
        juce::AudioProcessorEditor* createEditor() override;
        void    prepareToPlay (double sampleRate, int samplesPerBlock) override;
        void    releaseResources() override;
        bool    isBusesLayoutSupported (const BusesLayout& layouts) const override { return true; };
        void    processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
        bool    hasEditor() const override              { return true; }
        bool    acceptsMidi()  const override           { return true;  };
        bool    producesMidi() const override           { return false; };
        bool    isMidiEffect() const override           { return false; };
        double  getTailLengthSeconds() const override   { return 0.0; };
        int     getNumPrograms()    override;
        int     getCurrentProgram() override;
        void    setCurrentProgram (int index) override;
        const   juce::String getName() const override   { return JucePlugin_Name; };
        const   juce::String getProgramName (int index) override;
        void    changeProgramName (int index, const juce::String& newName) override;
        void    getStateInformation (juce::MemoryBlock& destData) override;
        void    setStateInformation (const void* data, int sizeInBytes) override;

        void    translateMidi(const juce::MidiMessage&);
        
        cell::iospecs   settings;
        cell::sequence<float>* ovt;
        cell::wavering<cell::point3d<float>>* wBuffer; // Display buffer
        cell::feeder* feed;

        GribAudioProcessor();
       ~GribAudioProcessor() override;
    private:
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GribAudioProcessor)
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////