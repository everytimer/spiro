#include "fSlider.h"
#include <cmath>
fSlider::fSlider()
{
    setSliderStyle (juce::Slider::LinearBar);
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

fSlider::~fSlider(){}

void fSlider::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto h  = bounds.getHeight();
    auto w  = bounds.getWidth();
    auto xo = bounds.getCentreX();
    auto yo = bounds.getCentreY();
    
    g.setColour (findColour (juce::Slider::backgroundColourId));
    g.fillRect(bounds);
    
    g.setColour (findColour (juce::Slider::trackColourId));
    g.drawRect(bounds);
    auto f = getValue();
    g.fillRect(0.0, 0.0, f*w, h);
}

void fSlider::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);
    setMouseCursor (juce::MouseCursor::NoCursor);
}

void fSlider::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);
    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());
    setMouseCursor (juce::MouseCursor::NormalCursor);
}