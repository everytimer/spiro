#include "ListSlider.h"

ListSlider::ListSlider()
{
    setSliderStyle (juce::Slider::LinearBar );
    setColour (juce::Slider::trackColourId, juce::Colours::transparentWhite);
    setTextBoxIsEditable (false);
    setRange (0.0f, 10.0f, 1.0f);
    setValue (0.0);
    setTextValueSuffix ("");
    setWantsKeyboardFocus (true);
}

ListSlider::~ListSlider(){}

void ListSlider::paint (juce::Graphics& g)
{
    g.fillAll(findColour (juce::Slider::backgroundColourId));
    auto bounds = getLocalBounds().toFloat();
    auto h = bounds.getHeight();
    auto w = bounds.getWidth();
    g.setColour (findColour (juce::Slider::textBoxOutlineColourId));

    auto c = (getValue()-getMinimum())/(getRange().getLength()+1.0f);
    auto sw = w / (getRange().getLength()+1.0f);

    g.fillRect( c*w, 0.0f, sw, h);
}

void ListSlider::mouseDown (const juce::MouseEvent& event)
{
    juce::Slider::mouseDown (event);
    setMouseCursor (juce::MouseCursor::NoCursor);
}

void ListSlider::mouseUp (const juce::MouseEvent& event)
{
    juce::Slider::mouseUp (event);
    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition (event.source.getLastMouseDownPosition());
    setMouseCursor (juce::MouseCursor::NormalCursor);
}