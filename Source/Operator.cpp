#include "Operator.h"



Operator::Operator()
{
    // setResizable(false, false);
    // setSize (WIDTH, HEIGHT);


    coarse.setRange (40, 8000, 0);
    coarse.setTextValueSuffix (" Hz");
    coarse.setNumDecimalPlacesToDisplay (0);
    coarse.setColour(juce::Slider::textBoxTextColourId, colour_set[4]);
    coarse.setColour(juce::Slider::textBoxOutlineColourId, colour_set[4]);

    fine.setColour  (juce::Slider::textBoxTextColourId, colour_set[3]);
    fine.setColour  (juce::Slider::textBoxOutlineColourId, colour_set[3]);

    theta.setColour (juce::Slider::textBoxTextColourId, colour_set[2]);
    theta.setColour (juce::Slider::textBoxOutlineColourId, colour_set[2]);

    fm.setColour    (juce::Slider::textBoxTextColourId, colour_set[0]);
    fm.setColour    (juce::Slider::textBoxOutlineColourId, colour_set[0]);

    warp.setColour  (juce::Slider::textBoxTextColourId, colour_set[0]);
    warp.setColour  (juce::Slider::textBoxOutlineColourId, colour_set[0]);

    amp.setColour   (juce::Slider::textBoxTextColourId, colour_set[5]);
    amp.setColour   (juce::Slider::textBoxOutlineColourId, colour_set[5]);





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

    g.setColour(colour_set[4]);
    g.drawLine (s*1, (bh + gap) * 0 + ch, ctrl_area.getWidth(), (bh + gap) * 0 + ch, 1.0f);
    g.drawLine (s*1, (bh + gap) * 0 + ch, s*1, area.getHeight()-lh*0, 1.0f);
    g.drawLine (s*1, area.getHeight()-lh*0, area.getWidth()/3.0f, area.getHeight()-lh*0, 1.0f);


    g.setColour(colour_set[3]);
    g.drawLine (s*2, (bh + gap) * 1 + ch, ctrl_area.getWidth(), (bh + gap) * 1 + ch, 1.0f);
    g.drawLine (s*2, (bh + gap) * 1 + ch, s*2, area.getHeight()-lh*1, 1.0f);
    g.drawLine (s*2, area.getHeight()-lh*1, area.getWidth()/3.0f, area.getHeight()-lh*1, 1.0f);


    g.setColour(colour_set[2]);
    g.drawLine (s*3, (bh + gap) * 2 + ch, ctrl_area.getWidth(), (bh + gap) * 2 + ch, 1.0f);
    g.drawLine (s*3, (bh + gap) * 2 + ch, s*3, area.getHeight()-lh*2, 1.0f);
    g.drawLine (s*3, area.getHeight()-lh*2, area.getWidth()/3.0f, area.getHeight()-lh*2, 1.0f);

    g.setColour(colour_set[0]);
    g.drawLine (s*4, (bh + gap) * 3 + ch, ctrl_area.getWidth(), (bh + gap) * 3 + ch, 1.0f);
    g.drawLine (s*4, (bh + gap) * 3 + ch, s*4, area.getHeight()-lh*3, 1.0f);
    g.drawLine (s*4, area.getHeight()-lh*3, area.getWidth()/3.0f, area.getHeight()-lh*3, 1.0f);

    g.setColour(colour_set[0]);
    g.drawLine (s*5, (bh + gap) * 4 + ch, ctrl_area.getWidth(), (bh + gap) * 4 + ch, 1.0f);
    g.drawLine (s*5, (bh + gap) * 4 + ch, s*5, area.getHeight()-lh*4, 1.0f);
    g.drawLine (s*5, area.getHeight()-lh*4, area.getWidth()/3.0f, area.getHeight()-lh*4, 1.0f);

    g.setColour(colour_set[5]);
    g.drawLine (s*6, (bh + gap) * 5 + ch, ctrl_area.getWidth(), (bh + gap) * 5 + ch, 1.0f);
    g.drawLine (s*6, (bh + gap) * 5 + ch, s*6, area.getHeight()-lh*5, 1.0f);
    g.drawLine (s*6, area.getHeight()-lh*5, area.getWidth()/3.0f, area.getHeight()-lh*5, 1.0f);


    g.setColour(colour_set[5]);

    g.drawLine (t_area.getWidth() -     1, (bh + gap) * 5 + ch*2, t_area.getWidth() -     1, area.getHeight()-lh*3, 1.0f);
    g.drawLine (t_area.getWidth() -     1, area.getHeight()-lh*3, s*17, area.getHeight()-lh*3, 1.0f);

    g.drawLine (t_area.getWidth() -   s-1, (bh + gap) * 5 + ch*2, t_area.getWidth() -   s-1, area.getHeight()-lh*4, 1.0f);
    g.drawLine (t_area.getWidth() -   s-1, area.getHeight()-lh*4, s*17, area.getHeight()-lh*4, 1.0f);

    g.drawLine (t_area.getWidth() - s*2-1, (bh + gap) * 5 + ch*2, t_area.getWidth() - s*2-1, area.getHeight()-lh*5, 1.0f);
    g.drawLine (t_area.getWidth() - s*2-1, area.getHeight()-lh*5, s*17, area.getHeight()-lh*5, 1.0f);


}

void Operator::resized ()
{
    area = getLocalBounds();
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