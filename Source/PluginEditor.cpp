//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "PluginProcessor.h"
#include "PluginEditor.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GribAudioProcessorEditor::GribAudioProcessorEditor (GribAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("B612 Mono");
    setResizable(false, false);
    setSize (WIDTH, HEIGHT);
    setWantsKeyboardFocus (true);


    spdXYZ.outline      = colour_set[9];
    spdXYZ.background   = colour_set[7];

    wdVolume.setColour  (juce::Slider::trackColourId, colour_set[9]);
    wdVolume.setColour  (juce::Slider::backgroundColourId, colour_set[7]);

    form_a.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    form_a.setColour (juce::Slider::backgroundColourId, colour_set[7]);

    form_b.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    form_b.setColour (juce::Slider::backgroundColourId, colour_set[7]);

    form_c.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    form_c.setColour (juce::Slider::backgroundColourId, colour_set[7]);

    form_d.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    form_d.setColour (juce::Slider::backgroundColourId, colour_set[7]);

    form_e.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    form_e.setColour (juce::Slider::backgroundColourId, colour_set[7]);

    form_f.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    form_f.setColour (juce::Slider::backgroundColourId, colour_set[7]);


    addAndMakeVisible (wdVolume);
    addAndMakeVisible (operator_a);
    addAndMakeVisible (operator_b);
    addAndMakeVisible (operator_c);
    addAndMakeVisible (operator_d);
    addAndMakeVisible (operator_e);
    addAndMakeVisible (operator_f);

    addAndMakeVisible (form_a);
    addAndMakeVisible (form_b);
    addAndMakeVisible (form_c);
    addAndMakeVisible (form_d);
    addAndMakeVisible (form_e);
    addAndMakeVisible (form_f);

    addAndMakeVisible (eds);

    addAndMakeVisible (SC);
    // addAndMakeVisible (SS);

    addAndMakeVisible (spdXYZ);


    rWaveDisplay.setBounds (680, 240, 192,  96);
    rSpectreDisplay.setBounds (680, 340, 192,  96);
    rSpiroDisplay.setBounds(680,  42, 192, 192);


    operator_a.coarse.onValueChange = [this] { audioProcessor.feed->renderer->v[0].vco[0].set_delta(operator_a.coarse.getValue());};
    operator_a.theta.onValueChange  = [this] { audioProcessor.feed->renderer->cvs->set(0, 0, operator_a.theta.getValue()); };
    operator_a.fm.onValueChange     = [this] { audioProcessor.feed->renderer->cvs->set(0, 1, operator_a.fm.getValue()); };
    operator_a.warp.onValueChange   = [this] { audioProcessor.feed->renderer->cvs->set(0, 2, operator_a.warp.getValue()); };
    operator_a.amp.onValueChange    = [this] { audioProcessor.feed->renderer->cvs->set(0, 3, operator_a.amp.getValue()); };
    form_a.textFromValueFunction    = [](double value) { return wforms[uint(value)]; };
    form_a.onValueChange            = [this] { audioProcessor.feed->renderer->cvs->set(0, 4, form_a.getValue()); };


    operator_b.coarse.onValueChange = [this] { audioProcessor.feed->renderer->v[0].vco[1].set_delta(operator_b.coarse.getValue());};
    operator_b.theta.onValueChange  = [this] { audioProcessor.feed->renderer->cvs->set(1, 0, operator_b.theta.getValue()); };
    operator_b.fm.onValueChange     = [this] { audioProcessor.feed->renderer->cvs->set(1, 1, operator_b.fm.getValue()); };
    operator_b.warp.onValueChange   = [this] { audioProcessor.feed->renderer->cvs->set(1, 2, operator_b.warp.getValue()); };
    operator_b.amp.onValueChange    = [this] { audioProcessor.feed->renderer->cvs->set(1, 3, operator_b.amp.getValue()); };
    form_b.textFromValueFunction    = [](double value) { return wforms[uint(value)]; };
    form_b.onValueChange            = [this] { audioProcessor.feed->renderer->cvs->set(1, 4, form_b.getValue()); };

    operator_c.coarse.onValueChange = [this] { audioProcessor.feed->renderer->v[0].vco[2].set_delta(operator_c.coarse.getValue()); };
    operator_c.theta.onValueChange  = [this] { audioProcessor.feed->renderer->cvs->set(2, 0, operator_c.theta.getValue()); };
    operator_c.fm.onValueChange     = [this] { audioProcessor.feed->renderer->cvs->set(2, 1, operator_c.fm.getValue()); };
    operator_c.warp.onValueChange   = [this] { audioProcessor.feed->renderer->cvs->set(2, 2, operator_c.warp.getValue()); };
    operator_c.amp.onValueChange    = [this] { audioProcessor.feed->renderer->cvs->set(2, 3, operator_c.amp.getValue()); };
    form_c.textFromValueFunction    = [](double value) { return wforms[uint(value)]; };
    form_c.onValueChange            = [this] { audioProcessor.feed->renderer->cvs->set(2, 4, form_c.getValue()); };

    spdXYZ.X.onValueChange     = [this] { audioProcessor.feed->renderer->angle[0] = spdXYZ.X.getValue(); };
    spdXYZ.Y.onValueChange     = [this] { audioProcessor.feed->renderer->angle[1] = spdXYZ.Y.getValue(); };
    spdXYZ.Z.onValueChange     = [this] { audioProcessor.feed->renderer->angle[2] = spdXYZ.Z.getValue(); };

    wdVolume.onValueChange     = [this] { audioProcessor.feed->renderer->volume = wdVolume.getValue(); };


    spCanvas = new cell::frame<float>(rSpiroDisplay.getWidth(), rSpiroDisplay.getHeight());
    spCanvas->clr(0.0f);
    wdCanvas = new cell::frame<float>(rWaveDisplay.getWidth(), rWaveDisplay.getHeight());
    wdCanvas->clr(0.0f);
    sdCanvas = new cell::frame<float>(rSpectreDisplay.getWidth(), rSpectreDisplay.getHeight());
    sdCanvas->clr(0.0f);
    startTimerHz(30);

}

GribAudioProcessorEditor::~GribAudioProcessorEditor()
{
    delete sdCanvas;
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
    
    g.setColour(colour_set[7]);
    g.fillRect (rWaveDisplay);
    g.setColour(colour_set[7]);
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
        lineSDFAABB(wdCanvas, i, yo, i, yc, 0.5f, 0.01f);
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
    float h  = rSpectreDisplay.getHeight();
    int w    = rSpectreDisplay.getWidth();
    float cy = h / 2.0f;
    float cx = w / 2.0f;

    cell::spectre spectrum(w, 48000);
    float* B = new float[w];
    spectrum.in = B;

    static auto layer = juce::Image (juce::Image::PixelFormat::ARGB, w, h, true);
    static juce::Image::BitmapData bmp(layer, juce::Image::BitmapData::ReadWriteMode::readWrite);

    g.setColour(colour_set[7]);
    g.fillRect (rSpectreDisplay);
    g.setColour(colour_set[7]);
    g.drawRect (rSpectreDisplay);

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
        drawLineV(sdCanvas, i, h/2, yc, 1.0f);
        // lineSDFAABB(sdCanvas, i, yo, i, yc, 0.5f, 0.05f);
    }
    cell::boxBlur(sdCanvas);

    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            float c = sdCanvas->get(x, y);
            bmp.setPixelColour (x, y, juce::Colour::fromFloatRGBA (1.09f, 0.71f*c*2, 0.20f, c));
            sdCanvas->set(x, y, sdCanvas->get(x, y) * 0.9f);
        }
    }
        
    g.setOpacity (1.0f);
    g.drawImageAt(layer, rSpectreDisplay.getX(), rSpectreDisplay.getY());
    delete[] B;
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

    g.setColour(colour_set[7]);
    g.drawRect (rSpiroDisplay);

    g.setColour(colour_set[7]);
    g.fillRect (rSpiroDisplay);

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
    g.fillAll       (colour_set[6]);
    // g.setColour     (cFastBlack);
    // g.drawRect      (0, 0, WIDTH, HEIGHT);
    WaveDisplay     (g,  80.0f);
    // SpectralDisplay (g, 100.0f);
    SpiroDisplay    (g, 500.0f);
}

void GribAudioProcessorEditor::resized()
{
    SC.setBounds        (   4, 200, 512, 192);
    // SS.setBounds        (   550, 200, 64, 64);

    form_a.setBounds(  8,  18, 92, 18);
    form_b.setBounds(108,  18, 92, 18);
    form_c.setBounds(208,  18, 92, 18);
    form_d.setBounds(308,  18, 92, 18);
    form_e.setBounds(408,  18, 92, 18);
    form_f.setBounds(508,  18, 92, 18);

    // eds.setBounds(400,300,192,96);
    eds.setBounds ( 8, 400, 256, 96);

    operator_a.setBounds(   4,  40, 96, 288);
    operator_b.setBounds( 104,  40, 96, 288);
    operator_c.setBounds( 204,  40, 96, 288);
    operator_d.setBounds( 304,  40, 96, 288);
    operator_e.setBounds( 404,  40, 96, 288);
    operator_f.setBounds( 504,  40, 96, 288);


    wdVolume.setBounds  ( 680,  20, 192,  16);
    spdXYZ.setBounds    ( 630,  42,  45, 296);


}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////