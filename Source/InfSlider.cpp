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

    g.setColour  (findColour (juce::Slider::trackColourId));
    auto colour = findColour (juce::Slider::trackColourId);
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