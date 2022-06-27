//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Interface.h"
#include "serpent/blur.hpp"
#include "serpent/primitives.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GribAudioProcessorEditor::GribAudioProcessorEditor (GribAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    setResizable(false, false);
    setSize (WIDTH, HEIGHT);
    setWantsKeyboardFocus (true);

    nbCoarse.setColour (juce::Slider::textBoxTextColourId, cBlue);
    nbCoarse.setColour (juce::Slider::textBoxOutlineColourId, cBlue);
    nbCoarse.setRange  (40, 8000, 0);
    nbCoarse.setTextValueSuffix (" Hz");
    nbCoarse.setNumDecimalPlacesToDisplay (0);


    nbVolume.setColour (juce::Slider::textBoxTextColourId, cGreen);
    nbVolume.setColour (juce::Slider::textBoxOutlineColourId, cGreen);

    nbDetune.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbDetune.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbWarp.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbWarp.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbAmp.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbAmp.setColour (juce::Slider::textBoxOutlineColourId, cYellow);


    nbH1.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH1.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH2.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH2.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH3.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH3.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH4.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH4.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH5.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH5.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH6.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH6.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH7.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH7.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    nbH8.setColour (juce::Slider::textBoxTextColourId, cYellow);
    nbH8.setColour (juce::Slider::textBoxOutlineColourId, cYellow);

    addAndMakeVisible (nbCoarse);
    addAndMakeVisible (nbVolume);
    addAndMakeVisible (nbDetune);
    addAndMakeVisible (nbWarp);
    addAndMakeVisible (nbAmp);

    addAndMakeVisible (nbH1);
    addAndMakeVisible (nbH2);
    addAndMakeVisible (nbH3);
    addAndMakeVisible (nbH4);
    addAndMakeVisible (nbH5);
    addAndMakeVisible (nbH6);
    addAndMakeVisible (nbH7);
    addAndMakeVisible (nbH8);
    addAndMakeVisible (SC);

    rWaveDisplay.setBounds  (20, 45, 256, 128);
    rSpiroDisplay.setBounds(280, 45, 192, 128);

    nbCoarse.onValueChange  = [this] { audioProcessor.feed->renderer->trigger(nbCoarse.getValue()); };
    // nbFM.onValueChange      = [this] { audioProcessor.osc2.frequency = nbFM.getValue(); audioProcessor.osc2.set_delta(); };

    nbVolume.onValueChange     = [this] { audioProcessor.feed->renderer->volume = nbVolume.getValue(); };
    // nbDetune.onValueChange  = [this] { audioProcessor.osc.shift = nbDetune.getValue(); audioProcessor.osc.set_shift();};
    // nbWarp.onValueChange    = [this] { audioProcessor.osc.warp = nbWarp.getValue(); };
    // nbAmp.onValueChange     = [this] { audioProcessor.osc.amplitude = nbAmp.getValue(); };

    // nbH1.onValueChange      = [this] { audioProcessor.ovt->data[0] = nbH1.getValue(); };
    // nbH2.onValueChange      = [this] { audioProcessor.ovt->data[1] = nbH2.getValue(); };
    // nbH3.onValueChange      = [this] { audioProcessor.ovt->data[2] = nbH3.getValue(); };
    // nbH4.onValueChange      = [this] { audioProcessor.ovt->data[3] = nbH4.getValue(); };
    // nbH5.onValueChange      = [this] { audioProcessor.ovt->data[4] = nbH5.getValue(); };
    // nbH6.onValueChange      = [this] { audioProcessor.ovt->data[5] = nbH6.getValue(); };
    // nbH7.onValueChange      = [this] { audioProcessor.ovt->data[6] = nbH7.getValue(); };
    // nbH8.onValueChange      = [this] { audioProcessor.ovt->data[7] = nbH8.getValue(); };
    spCanvas = new cell::frame<float>(rSpiroDisplay.getWidth(), rSpiroDisplay.getHeight());
    spCanvas->clr(0.0f);
    wdCanvas = new cell::frame<float>(rWaveDisplay.getWidth(), rWaveDisplay.getHeight());
    wdCanvas->clr(0.0f);
    startTimerHz(60);

}

GribAudioProcessorEditor::~GribAudioProcessorEditor()
{
    delete wdCanvas;
    delete spCanvas;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GribAudioProcessorEditor::WaveDisplay(juce::Graphics& g, float scale)
{
    float h  = rWaveDisplay.getHeight();
    float w  = rWaveDisplay.getWidth();
    float cy = h / 2.0f;
    float cx = w / 2.0f;

    static auto layer = juce::Image (juce::Image::PixelFormat::ARGB, w, h, true);
    static juce::Image::BitmapData bmp(layer, juce::Image::BitmapData::ReadWriteMode::readWrite);

    g.setColour(cYellow);
    g.drawRect (rWaveDisplay);

    int yo, yc;

    float a = audioProcessor.wBuffer->get().y; 
    float b = audioProcessor.wBuffer->get().y;
    while (((a + b) < 0.0f) || (b > 0.0f)) // Search for zero crossings
    {
        a = audioProcessor.wBuffer->get().y; 
        b = audioProcessor.wBuffer->get().y;
    }
    yc = b * scale + cy;
    for(int i = 3; i < w - 3; i++)
    {
        yo = yc;
        yc = audioProcessor.wBuffer->get().y * scale + cy;
        DrawLineB(wdCanvas, i, yo, i, yc, 1.0f);
    }
    cell::boxBlur(wdCanvas);

    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            float c = wdCanvas->get(x, y);
            bmp.setPixelColour (x, y, juce::Colour::fromFloatRGBA (1.09f, 0.71f*c*2, 0.20f, c));
            wdCanvas->set(x, y, wdCanvas->get(x, y) * 0.9f);
        }
    }
        
    g.setOpacity (1.0f);
    g.drawImageAt(layer, rWaveDisplay.getX(), rWaveDisplay.getY());
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GribAudioProcessorEditor::SpiroDisplay(juce::Graphics& g, float scale, int iterations = 16)
{
    float yo = rSpiroDisplay.getY();
    float xo = rSpiroDisplay.getX();
    
    float h = rSpiroDisplay.getHeight();
    float w = rSpiroDisplay.getWidth();
    
    float cy = h / 2;
    float cx = w / 2;
    
    static auto layer = juce::Image (juce::Image::PixelFormat::ARGB, w, h, true);
    static juce::Image::BitmapData bmp(layer, juce::Image::BitmapData::ReadWriteMode::readWrite);

    g.setColour(cYellow);
    g.drawRect (rSpiroDisplay);
    juce::Rectangle<float> pointArea (3, 3);
    juce::Point<float> position;

    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < iterations; j++)
        {
            spCanvas->set(  audioProcessor.wBuffer->get().x * scale + cx, 
                            audioProcessor.wBuffer->get().y * scale + cy, 1.0f);
        }
    }
   
    cell::boxBlur(spCanvas);

    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            float c = spCanvas->get(x, y);
            bmp.setPixelColour (x, y, juce::Colour::fromFloatRGBA (1.09f, 0.71f * c * 2, 0.20f, c));
            spCanvas->set(x, y, spCanvas->get(x, y) * 0.9f);
        }
    }
    
    g.setOpacity (1.0f);
    g.drawImageAt(layer, xo, yo);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GribAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll   (cAsphaltGrey);
    g.setColour (cFastBlack);
    g.drawRect  (0, 0, WIDTH, HEIGHT);
    WaveDisplay (g, 80.0f);
    SpiroDisplay(g, 80.0f);
}

void GribAudioProcessorEditor::resized()
{
    nbCoarse.setBounds ( 20,  20, 60, 20);
    nbVolume.setBounds ( 85,  20, 60, 20);
    nbDetune.setBounds (150,  20, 60, 20);
    nbWarp.setBounds   (215,  20, 60, 20);
    nbAmp.setBounds    (280,  20, 60, 20);

    nbH1.setBounds     ( 20, 400, 60, 20);
    nbH2.setBounds     ( 85, 400, 60, 20);
    nbH3.setBounds     (150, 400, 60, 20);
    nbH4.setBounds     (215, 400, 60, 20);
    nbH5.setBounds     (280, 400, 60, 20);
    nbH6.setBounds     (345, 400, 60, 20);
    nbH7.setBounds     (410, 400, 60, 20);
    nbH8.setBounds     (475, 400, 60, 20);
    
    SC.setBounds      (20, 180, 300, 200);


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////