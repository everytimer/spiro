#include "EnvelopeDisplay.h"
#include "serpent/sdfaabb.hpp"


EnvelopeDisplay::EnvelopeDisplay (): npa(this), npd(this), nps(this), npr(this)
{
    setSize (256, 96);

    addAndMakeVisible (npa);
    addAndMakeVisible (npd);
    addAndMakeVisible (nps);
    addAndMakeVisible (npr);
    addAndMakeVisible (ENV_A);
    addAndMakeVisible (ENV_B);
    addAndMakeVisible (ENV_C);
    addAndMakeVisible (ENV_D);
    addAndMakeVisible (ENV_E);
    addAndMakeVisible (ENV_F);

    ENV_A.setRadioGroupId(radio_id);
    ENV_B.setRadioGroupId(radio_id);
    ENV_C.setRadioGroupId(radio_id);
    ENV_D.setRadioGroupId(radio_id);
    ENV_E.setRadioGroupId(radio_id);
    ENV_F.setRadioGroupId(radio_id);

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
    npa.cr = npd.x - radius;
    npd.cl = npa.x + radius;
    npd.cr = nps.x - radius;
    nps.cl = npd.x + radius;
    nps.cr = npr.x - radius;
    npr.cl = nps.x + radius;

    g.setColour(colour_set[9]);
    g.drawRect(display);
    updateNodes();
    plot(g, 0.0f);
    g.setColour(colour_set[7]);

    g.drawLine(npa.x, 2, npa.x, display.getHeight()-4, 1.0f);
    g.drawLine(npd.x, 2, npd.x, display.getHeight()-4, 1.0f);
    g.drawLine(nps.x, 2, nps.x, display.getHeight()-4, 1.0f);
    g.drawLine(npr.x, 2, npr.x, display.getHeight()-4, 1.0f);
}

void EnvelopeDisplay::resized()
{
    area = getLocalBounds();
    display = area.withTrimmedRight(area.getWidth()/12.0f);
    npa.cb = npd.cb = nps.cb = npr.cb = display.getHeight() - radius;

    auto b_area = area.withTrimmedLeft(area.getWidth()/14.0f*13.0f).withTrimmedBottom(area.getHeight()/7.0f*6.0f);
    auto gap = display.getHeight()/38.0f;
    ENV_A.setBounds(b_area);
    ENV_B.setBounds(b_area.withY((b_area.getHeight()+gap)*1));
    ENV_C.setBounds(b_area.withY((b_area.getHeight()+gap)*2));
    ENV_D.setBounds(b_area.withY((b_area.getHeight()+gap)*3));
    ENV_E.setBounds(b_area.withY((b_area.getHeight()+gap)*4));
    ENV_F.setBounds(b_area.withY((b_area.getHeight()+gap)*5));



    npa.setBounds ( 20, 20, diameter, diameter);
    npa.cr = display.getWidth()/4 - radius;
    npa.cl = radius;

    npd.setBounds ( 80, 40, diameter, diameter);
    npd.cr = display.getWidth()/2 - radius;
    npd.cl = display.getWidth()/4 + radius;

    nps.setBounds (140, 60, diameter, diameter);
    nps.cr = display.getWidth()/4*3 - radius;
    nps.cl = display.getWidth()/2 + radius;

    npr.setBounds (200, 80, diameter, diameter);
    npr.cr = display.getWidth() - radius;
    npr.cl = display.getWidth()/4*3 + radius;

    canvas = new cell::frame<float>(display.getWidth(), display.getHeight());
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
    
    env.start();
    float py, cy = env.iterate();
    float px, cx = 0.0f;
    for(int i = 0; i < w; i++)
    {
        py = cy;
        px = cx;
        cx = i;
        cy = env.iterate();

        drawLineV(canvas, i, h- cy, h-1, 0.4f);
        lineSDFAABB(canvas, px, h-py, cx, h-cy, rR , aA);
    }
    cell::alphaGradientFrame(canvas, 4);
    cell::boxBlur(canvas, 1, -0.1f);

    
    for(int y = 0; y < h-1; y++)
    {
        for(int x = 1; x < w-1; x++)
        {
            float c = canvas->get(x, y);
            bmp.setPixelColour (x, y, juce::Colour::fromFloatRGBA (0.20f, 0.8f*c, 0.40f, c));
        }
    }

    g.drawImageAt(layer, xo, yo);
    canvas->clr(0.0f);
}


void EnvelopeDisplay::mouseDown(const juce::MouseEvent& event)
{
    std::cout<<"X: "<<event.x<<"\n";
    std::cout<<"Y: "<<event.y<<"\n";

    if((event.x>0)&&(event.x<npa.x))
    {
        env.node[1].curve == 3? env.node[1].curve = 0 : env.node[1].curve++;
        repaint();
    }
    else if((event.x>npa.x)&&(event.x<npd.x))
    {
        env.node[2].curve == 3? env.node[2].curve = 0 : env.node[2].curve++;
        repaint();
    }
    else if((event.x>npd.x)&&(event.x<nps.x))
    {
        env.node[3].curve == 3? env.node[3].curve = 0 : env.node[3].curve++;
        repaint();
    }
    else if((event.x>nps.x)&&(event.x<npr.x))
    {
        env.node[4].curve == 3? env.node[4].curve = 0 : env.node[4].curve++;
        repaint();
    }
    else if((event.x>npr.x)&&(event.x<display.getWidth()))
    {
        env.node[5].curve == 3? env.node[5].curve = 0 : env.node[5].curve++;
        repaint();
    }
}