#include "NumberBox.h"

NumberBox::NumberBox()
{
    setSliderStyle (juce::Slider::LinearBarVertical);
    setColour (juce::Slider::trackColourId, juce::Colours::transparentWhite);
    setTextBoxIsEditable (false);
    setVelocityBasedMode (true);
    setVelocityModeParameters (0.1, 1, 0.09, false);
    setRange (0.0f, 1.0f, 0.001f);
    setValue (0.0);
    setDoubleClickReturnValue (true, 0.5f);
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

NumberBox::~NumberBox(){}

void NumberBox::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    auto h = bounds.getHeight();
    auto w = bounds.getWidth();
    g.setColour (findColour (juce::Slider::textBoxOutlineColourId));

    auto c = getValue();
    auto l = h / 8.0f;

    g.fillRect( w - w / 8.0f, 
                h - c * (h - l) - l, 
                w, 
                l
                );


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

void NumberBox::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);
    setMouseCursor (juce::MouseCursor::NoCursor);
}

void NumberBox::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);
    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());
    setMouseCursor (juce::MouseCursor::NormalCursor);
}