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

}

NumberBox::~NumberBox(){}

void NumberBox::paint (juce::Graphics& g)
{
    g.fillAll(findColour (juce::Slider::textBoxBackgroundColourId));
    auto bounds = getLocalBounds().toFloat();
    auto h = bounds.getHeight();
    auto w = bounds.getWidth();
    g.setColour (findColour (juce::Slider::textBoxOutlineColourId));

    auto c = (getValue()-getMinimum())/getRange().getLength();
    auto l = h / 8.0f;

    g.fillRect( w - w / 8.0f, 
                h - c * (h - l) - l, 
                w, 
                l
                );
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

// void NumberBox::mouseEnter (const juce::MouseEvent& event)
// {
//     setColour(juce::Slider::textBoxOutlineColourId, hoveredColour); // 3 : PaleOlive
//     repaint();
// }

// void NumberBox::mouseExit (const juce::MouseEvent& event)
// {
//     setColour(juce::Slider::textBoxOutlineColourId, normalColour);
//     repaint();
// }