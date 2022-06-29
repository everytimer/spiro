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
    // onValueChange = [&]()
    // {
    //     if (getValue() < 10)
    //         setNumDecimalPlacesToDisplay(2);
    //     else if (10 <= getValue() && getValue() < 100)
    //         setNumDecimalPlacesToDisplay(1);
    //     else
    //         setNumDecimalPlacesToDisplay(0);
    // };
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
    // g.fillRoundedRectangle(bounds, 4);
    g.drawRect(bounds);
    g.setColour (findColour (juce::Slider::trackColourId));
    auto f = getValue();
    g.fillRect(0.0, 0.0, f*w, h);


    // g.drawEllipse(bounds.getX()+h/8, bounds.getY()+h/8, h-h/4, h-h/4, 1.0f);

    // g.fillEllipse(sin(c)*h/2.7+xo - h/16, cos(c)*h/2.7+yo - h/16, h/8, h/8);

    

    // if (hasKeyboardFocus (false))
    // {

        // auto len = juce::jmin (h, w) * 0.15f;
        // auto thick  = len / 1.8f;


        // Left top
        // g.drawLine (0.0f, 0.0f, 0.0f, len, thick);
        // g.drawLine (0.0f, 0.0f, len, 0.0f, thick);

        // // Left bottom
        // g.drawLine (0.0f, h, 0.0f, h - len, thick);
        // g.drawLine (0.0f, h, len, h, thick);

        // // Right top
        // g.drawLine (w, 0.0f, w, len, thick);
        // g.drawLine (w, 0.0f, w - len, 0.0f, thick);

        // // Right bottom
        // g.drawLine (w, h, w, h - len, thick);
        // g.drawLine (w, h, w - len, h, thick);
    // }
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