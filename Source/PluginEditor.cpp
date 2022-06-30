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

    spRotateX.setColour (juce::Slider::trackColourId, colour_set[0]);
    spRotateX.setColour (juce::Slider::textBoxOutlineColourId, colour_set[0]);
    spRotateX.setRange  (0, M_PI * 2, 0);

    spRotateY.setColour (juce::Slider::trackColourId, colour_set[0]);
    spRotateY.setColour (juce::Slider::textBoxOutlineColourId, colour_set[0]);
    spRotateY.setRange  (0, M_PI * 2, 0);

    spRotateZ.setColour (juce::Slider::trackColourId, colour_set[0]);
    spRotateZ.setColour (juce::Slider::textBoxOutlineColourId, colour_set[0]);
    spRotateZ.setRange  (0, M_PI * 2, 0);

    wdVolume.setColour (juce::Slider::trackColourId, colour_set[0]);
    wdVolume.setColour (juce::Slider::backgroundColourId, colour_set[0]);

    addAndMakeVisible (wdVolume);

    addAndMakeVisible (operator_a);
    addAndMakeVisible (operator_b);
    addAndMakeVisible (operator_c);
    addAndMakeVisible (operator_d);

    addAndMakeVisible (SC);

    addAndMakeVisible (spRotateX);
    addAndMakeVisible (spRotateY);
    addAndMakeVisible (spRotateZ);


    rWaveDisplay.setBounds (680, 240, 192,  96);
    rSpiroDisplay.setBounds(680,  42, 192, 192);


    operator_a.coarse.onValueChange = [this] { audioProcessor.feed->renderer->trigger(operator_a.coarse.getValue()); };
    operator_a.theta.onValueChange  = [this] { audioProcessor.feed->renderer->trigger2(operator_a.theta.getValue()); };
    operator_a.fm.onValueChange     = [this] { audioProcessor.feed->renderer->vco[0].pwm = operator_a.fm.getValue(); };

    spRotateX.onValueChange    = [this] { audioProcessor.feed->renderer->angle[0] = spRotateX.getValue(); };
    spRotateY.onValueChange    = [this] { audioProcessor.feed->renderer->angle[1] = spRotateY.getValue(); };
    spRotateZ.onValueChange    = [this] { audioProcessor.feed->renderer->angle[2] = spRotateZ.getValue(); };

    wdVolume.onValueChange     = [this] { audioProcessor.feed->renderer->volume = wdVolume.getValue(); };


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

    g.setColour(colour_set[0]);
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

void GribAudioProcessorEditor::SpectralDisplay(juce::Graphics& g, float scale)
{
    float h  = rWaveDisplay.getHeight();
    int w  = rWaveDisplay.getWidth();
    float cy = h / 2.0f;
    float cx = w / 2.0f;

    cell::spectre spectrum(w, 48000);
    float* B = new float[w];
    spectrum.in = B;

    static auto layer = juce::Image (juce::Image::PixelFormat::ARGB, w, h, true);
    static juce::Image::BitmapData bmp(layer, juce::Image::BitmapData::ReadWriteMode::readWrite);

    g.setColour(colour_set[0]);
    g.drawRect (rWaveDisplay);

    int yo, yc;

    for(int i = 0; i < w ; i++)
    {
        B[i] = audioProcessor.wBuffer->get().y;
    }
    spectrum.process();

    yc = h*0.9-spectrum.out[0];
    for(int i = 0; i < w ; i++)
    {
        yo = yc;
        yc = h*0.9-spectrum.out[i] * scale;
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
    delete B;
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

    g.setColour(colour_set[0]);
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
    g.fillAll       (cAsphaltGrey);
    g.setColour     (cFastBlack);
    g.drawRect      (0, 0, WIDTH, HEIGHT);
    // WaveDisplay (g, 80.0f);
    SpectralDisplay (g,   1.0f);
    SpiroDisplay    (g, 500.0f);
}

void GribAudioProcessorEditor::resized()
{
    SC.setBounds        (   0, 180, 512, 192);

    operator_a.setBounds(   0,  20, 96, 288);
    operator_b.setBounds(  96,  20, 96, 288);
    operator_c.setBounds( 192,  20, 96, 288);
    operator_d.setBounds( 288,  20, 96, 288);

    wdVolume.setBounds  ( 680,  20, 192,  16);

    spRotateX.setBounds ( 660,  42 , 15,  60);
    spRotateY.setBounds ( 660, 108,  15,  60);
    spRotateZ.setBounds ( 660, 174,  15,  60);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////