#include "EnvelopeDisplay.h"
#include "serpent/sdfaabb.hpp"


EnvelopeDisplay::EnvelopeDisplay ():npa(this),npd(this),nps(this),npr(this)
{
    setSize (256, 128);
    canvas = new cell::frame<float>(256, 128);
    // setRepaintsOnMouseActivity(true);
    addAndMakeVisible (npa);
    addAndMakeVisible (npd);
    addAndMakeVisible (nps);
    addAndMakeVisible (npr);
    // addAndMakeVisible (A);
    // addAndMakeVisible (R);
    A.onValueChange     = [this] { aA = A.getValue(); repaint(); std::cout<<"A: "<<aA<<"\n"; };
    R.onValueChange     = [this] { rR = R.getValue(); repaint(); std::cout<<"R: "<<rR<<"\n"; };
}

EnvelopeDisplay::~EnvelopeDisplay()
{
    delete canvas;
}

void EnvelopeDisplay::updateNodes()
{
    env.node[1].value = display.getHeight() - npa.y;
    env.node[1].time  = npa.x;

    env.node[2].value = display.getHeight() - npd.y;
    env.node[2].time  = npd.x - npa.x;

    env.node[3].value = display.getHeight() - nps.y;
    env.node[3].time  = nps.x - npd.x;

    env.node[4].value = display.getHeight() - npr.y;
    env.node[4].time  = npr.x - nps.x;

    env.node[5].time  = display.getWidth()  - npr.x;

}

void EnvelopeDisplay::paint (juce::Graphics& g)
{
    g.fillAll(colour_set[6]);
    updateNodes();
    plot(g, 0.0f);
}

void EnvelopeDisplay::resized()
{
    area = getLocalBounds();
    display = area;

    npa.setBounds ( 20, 20, diameter, diameter);
    npd.setBounds ( 80, 40, diameter, diameter);
    nps.setBounds (140, 60, diameter, diameter);
    npr.setBounds (200, 80, diameter, diameter);
    // A.setBounds ( 10, 10, 80, 20);
    // R.setBounds ( 10, 40, 80, 20);
    updateNodes();
    repaint();
}



void EnvelopeDisplay::plot(juce::Graphics& g, float scale)
{
    float yo = display.getY();
    float xo = display.getX();
    
    float h = display.getHeight()-1;
    float w = display.getWidth();
    
    static auto layer = juce::Image (juce::Image::PixelFormat::ARGB, w, h, true);
    static juce::Image::BitmapData bmp(layer, juce::Image::BitmapData::ReadWriteMode::readWrite);

    g.setColour(colour_set[8]);
    g.drawRect (display);
    
    env.start();
    float py, cy = env.iterate();
    float px, cx = 0.0f;
    for(int i = 0; i < w; i++)
    {
        py = cy;
        px = cx;
        cx = i;
        cy = env.iterate();

        drawLineV(canvas, i, h- cy, h, 0.3f);
        lineSDFAABB(canvas, px, h-py, cx, h-cy, rR , aA);
    }
    cell::boxBlur(canvas, 1);

    
    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            float c = canvas->get(x, y);
            bmp.setPixelColour (x, y, juce::Colour::fromFloatRGBA (0.30f, 1.4f*c, 0.50f, c));
        }
    }

    g.drawImageAt(layer, xo, yo);
    canvas->clr(0.0f);
}
