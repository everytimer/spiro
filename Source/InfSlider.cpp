#include "InfSlider.h"
#include <cmath>
#include <iostream>


InfSlider::InfSlider()
{
    setSliderStyle (juce::Slider:: RotaryVerticalDrag);
    setRotaryParameters (0, 1, false);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    setColour (juce::Slider::trackColourId, juce::Colours::transparentWhite);
    setTextBoxIsEditable (false);
    setVelocityBasedMode (true);
    setVelocityModeParameters (0.1, 1, 0.09, false);
    setRange (0.0f, 1.0f, 0.001f);
    setValue (0.0);
    setDoubleClickReturnValue (true, 0.0f);
    setTextValueSuffix ("");
    setWantsKeyboardFocus (true);
}

InfSlider::~InfSlider(){}

void InfSlider::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto h  = bounds.getHeight();
    auto w  = bounds.getWidth();
    auto xo = bounds.getX();
    auto yo = bounds.getY();

    g.setColour  (findColour (juce::Slider::backgroundColourId));
    g.fillRect(bounds);


    g.setColour  (findColour (juce::Slider::trackColourId));
    auto v = getValue();

    g.drawRect(bounds);
    float c = v * h / ( M_PI * 2.0f );

    if (v < M_PI) g.fillRect(0.0f, c, w, h / 2.0f);
    else
    {
        g.fillRect(0.0f, 0.0f, w, c - h / 2.0f);
        g.fillRect(0.0f, c, w, h / 2.0f);
    }
}

void InfSlider::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);
    setMouseCursor (juce::MouseCursor::NoCursor);
}

void InfSlider::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);
    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());
    setMouseCursor (juce::MouseCursor::NormalCursor);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Rot3Slider::drawSBrace(juce::Graphics& g, float xo, float yo, float xe, float ye, float th, float cs = 1.0f)
{
    auto cx = (xo + xe)/2.0f * cs;

    g.drawLine(cx, yo, xe, yo, th);
    g.drawLine(cx, yo, cx, ye, th);
    g.drawLine(cx, ye, xo, ye, th);
}

void Rot3Slider::paint(juce::Graphics& g)
{
    g.setColour(colour_set[9]);
    // g.drawRect(area);
    float bh  = area.getHeight()/5.0f;
    float gap = bh/8.0f;

    drawSBrace(g, 0, bh/2               , area.getWidth()/1.5f, bh*4,                       1.0f, 0.7f );
    drawSBrace(g, 0, bh/2 +     bh + gap, area.getWidth()/1.5f, bh*4 +  bh/2 -    gap*0.75, 1.0f, 1.0f );
    drawSBrace(g, 0, bh/2 + (bh + gap)*2, area.getWidth()/1.5f, bh*4 + (bh/2)*2 - gap*1.25, 1.0f, 1.3f );

}

void Rot3Slider::resized()
{
    area = getLocalBounds();

    auto ctrl_area = area.withTrimmedLeft(area.getWidth()/1.5f).withHeight(area.getHeight()/5.0f);

    float bh  = area.getHeight()/5.0f;
    float gap = bh/8.0f;

    X.setBounds(ctrl_area.withY((bh + gap) * 0));
    Y.setBounds(ctrl_area.withY((bh + gap) * 1));
    Z.setBounds(ctrl_area.withY((bh + gap) * 2));


}


Rot3Slider::Rot3Slider()
{
    X.setColour (juce::Slider::trackColourId, colour_set[9]);
    X.setColour (juce::Slider::backgroundColourId, colour_set[7]);
    X.setRange  (0, M_PI * 2, 0);
    Y.setColour (juce::Slider::trackColourId, colour_set[9]);
    Y.setColour (juce::Slider::backgroundColourId, colour_set[7]);
    Y.setRange  (0, M_PI * 2, 0);
    Z.setColour (juce::Slider::trackColourId, colour_set[9]);
    Z.setColour (juce::Slider::backgroundColourId, colour_set[7]);
    Z.setRange  (0, M_PI * 2, 0);

    addAndMakeVisible (X);
    addAndMakeVisible (Y);
    addAndMakeVisible (Z);

}

Rot3Slider::~Rot3Slider()
{
}