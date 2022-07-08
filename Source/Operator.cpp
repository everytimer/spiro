#include "Operator.h"


void Operator::drawBrace(juce::Graphics& g, float xo, float yo, float xe, float ye, float th)
{
    g.drawLine(xo, yo, xe, yo, th);
    g.drawLine(xo, yo, xo, ye, th);
    g.drawLine(xo, ye, xe, ye, th);
}


Operator::Operator()
{
    // setResizable(false, false);
    // setSize (WIDTH, HEIGHT);


    coarse.setRange (40, 8000, 0);
    coarse.setTextValueSuffix (" Hz");
    coarse.setNumDecimalPlacesToDisplay (0);

    coarse.setColour(juce::Slider::textBoxTextColourId, colour_set[11]);
    coarse.setColour(juce::Slider::textBoxOutlineColourId, colour_set[9]);
    coarse.setColour(juce::Slider::textBoxBackgroundColourId, colour_set[7]);

    fine.setColour  (juce::Slider::textBoxTextColourId, colour_set[11]);
    fine.setColour  (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    fine.setColour  (juce::Slider::textBoxBackgroundColourId, colour_set[7]);

    theta.setColour (juce::Slider::textBoxTextColourId, colour_set[1]);
    theta.setColour (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    theta.setColour (juce::Slider::textBoxBackgroundColourId, colour_set[7]);

    fm.setColour    (juce::Slider::textBoxTextColourId, colour_set[1]);
    fm.setColour    (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    fm.setColour    (juce::Slider::textBoxBackgroundColourId, colour_set[7]);

    warp.setColour  (juce::Slider::textBoxTextColourId, colour_set[3]);
    warp.setColour  (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    warp.setColour  (juce::Slider::textBoxBackgroundColourId, colour_set[7]);

    amp.setColour   (juce::Slider::textBoxTextColourId, colour_set[3]);
    amp.setColour   (juce::Slider::textBoxOutlineColourId, colour_set[9]);
    amp.setColour   (juce::Slider::textBoxBackgroundColourId, colour_set[7]);






    addAndMakeVisible (coarse);
    addAndMakeVisible (fine);
    addAndMakeVisible (theta);
    addAndMakeVisible (fm);
    addAndMakeVisible (warp);
    addAndMakeVisible (amp);

};

Operator::~Operator()
{
}


void Operator::paint (juce::Graphics& g)
{
    // g.fillAll (cGreyLcd.withAlpha (0.1f));
    auto ctrl_area = t_area.withTrimmedRight(t_area.getWidth()/1.5f).withHeight(t_area.getHeight()/8.0f);
    auto ch  = ctrl_area.getHeight()/2.0f;
    auto bh  = t_area.getHeight()/8.0f;
    auto gap = bh/4.0f;
    auto s = ctrl_area.getWidth()/7.0f;

    auto lh = area.getHeight()/12.0f;

    g.setColour(colour_set[9]);
    drawBrace(g, s*1, (bh + gap) * 0 + ch, ctrl_area.getWidth(), area.getHeight()-lh*0, 1.0f);

    g.setColour(colour_set[9]);
    drawBrace(g, s*2, (bh + gap) * 1 + ch, ctrl_area.getWidth(), area.getHeight()-lh*1, 1.0f);

    g.setColour(colour_set[9]);
    drawBrace(g, s*3, (bh + gap) * 2 + ch, ctrl_area.getWidth(), area.getHeight()-lh*2, 1.0f);

    g.setColour(colour_set[9]);
    drawBrace(g, s*4, (bh + gap) * 3 + ch, ctrl_area.getWidth(), area.getHeight()-lh*3, 1.0f);

    g.setColour(colour_set[9]);
    drawBrace(g, s*5, (bh + gap) * 4 + ch, ctrl_area.getWidth(), area.getHeight()-lh*4, 1.0f);

    g.setColour(colour_set[9]);
    drawBrace(g, s*6, (bh + gap) * 5 + ch, ctrl_area.getWidth(), area.getHeight()-lh*5, 1.0f);

    g.setColour(colour_set[9]);
    drawBrace(g, t_area.getWidth()     -1, (bh + gap) * 5 + ch*2-1, s*17, area.getHeight()-lh*3, 1.0f);
    drawBrace(g, t_area.getWidth()   -s-1, (bh + gap) * 5 + ch*2-1, s*17, area.getHeight()-lh*4, 1.0f);
    drawBrace(g, t_area.getWidth() -s*2-1, (bh + gap) * 5 + ch*2-1, s*17, area.getHeight()-lh*5, 1.0f);

}

void Operator::resized ()
{
    area   = getLocalBounds();
    t_area = area.withTrimmedBottom(area.getHeight()/2.0f);
    auto ctrl_area = area.withTrimmedLeft(t_area.getWidth()/3.0f).withHeight(t_area.getHeight()/8.0f);
    auto bh  = t_area.getHeight()/8.0f;
    auto gap = bh/4.0f;
    coarse.setBounds (ctrl_area.withY((bh + gap) * 0));
    fine.setBounds   (ctrl_area.withY((bh + gap) * 1));
    theta.setBounds  (ctrl_area.withY((bh + gap) * 2));
    fm.setBounds     (ctrl_area.withY((bh + gap) * 3));
    warp.setBounds   (ctrl_area.withY((bh + gap) * 4));
    amp.setBounds    (ctrl_area.withY((bh + gap) * 5));

}