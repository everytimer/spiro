#include "SpriteSlider.h"


void SpriteSlider::paint(juce::Graphics& g)
{
    if (imageKnob.isValid())
    {
        const double rotation = (getValue()-getMinimum())/(getMaximum()-getMinimum());
        auto bounds = getLocalBounds();
        const int   frames  = imageKnob.getHeight() / imageKnob.getWidth();
        const int   frameId = (int)ceil(rotation * ((double)frames - 1.0f));
        const float radius  = juce::jmin(bounds.getWidth() / 2.0f, bounds.getHeight() / 2.0f);
        const float centerX = bounds.getX() + bounds.getWidth()  * 0.5f;
        const float centerY = bounds.getY() + bounds.getHeight() * 0.5f;
        const float rx = centerX - radius     - 1.0f;
        const float ry = centerY - radius;
        
        
        g.drawImage(imageKnob, (int)rx, (int)ry, 2 * (int)radius, 2 * (int)radius, 0, frameId*imageKnob.getWidth(), imageKnob.getWidth(), imageKnob.getWidth());
    }

}

SpriteSlider::SpriteSlider()
{   
    imageKnob = juce::ImageCache::getFromMemory(BinaryData::Knob_C01_png, BinaryData::Knob_C01_pngSize);
    setSliderStyle (juce::Slider:: RotaryVerticalDrag);
    // setRotaryParameters (0, 1, false);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    // setColour (juce::Slider::trackColourId, juce::Colours::transparentWhite);
    setTextBoxIsEditable (false);
    setVelocityBasedMode (true);
    setVelocityModeParameters (0.1, 1, 0.09, false);
    setRange (0.0f, 1.0f, 0.001f);
    setValue (0.0);
    setDoubleClickReturnValue (true, 0.0f);
    // setTextValueSuffix ("");
    // setWantsKeyboardFocus (true);
}

