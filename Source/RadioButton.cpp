#include "RadioButton.h"

RadioButton::RadioButton()
{
    setWantsKeyboardFocus (true);
}

RadioButton::~RadioButton(){}

void RadioButton::paint (juce::Graphics& g)
{
    if(getToggleState()) g.setColour(colour_set[9]);
    else g.setColour(colour_set[6]);
    g.fillRect(area);

    g.setColour(colour_set[9]);
    g.drawRect(area);
}

void RadioButton::resized()
{
    area = getLocalBounds();
}

// void RadioButton::mouseDown (const juce::MouseEvent& event)
// {

// }

// void RadioButton::mouseUp (const juce::MouseEvent& event)
// {

// }

// void RadioButton::mouseEnter (const juce::MouseEvent& event)
// {
//     setColour(juce::Slider::textBoxOutlineColourId, hoveredColour); // 3 : PaleOlive
//     repaint();
// }

// void RadioButton::mouseExit (const juce::MouseEvent& event)
// {
//     setColour(juce::Slider::textBoxOutlineColourId, normalColour);
//     repaint();
// }