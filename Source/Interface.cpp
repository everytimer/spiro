#include "Interface.h"


void Interface::drawRotarySlider(juce::Graphics& g,
                                       int x, int y, int width, int height, float sliderPos,
                                       float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    
    if (imageKnob.isValid())
    {
        const double rotation = (slider.getValue()
                                 - slider.getMinimum())
        / (slider.getMaximum()
           - slider.getMinimum());
        
        const int   frames = imageKnob.getHeight() / imageKnob.getWidth();
        const int   frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = juce::jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width     * 0.5f;
        const float centerY = y + height    * 0.5f;
        const float rx = centerX - radius   - 1.0f;
        const float ry = centerY - radius;
        
        
        g.drawImage(imageKnob,(int)rx,(int)ry,2 * (int)radius,2 * (int)radius,0,frameId*imageKnob.getWidth(),imageKnob.getWidth(), imageKnob.getWidth());
    }

}

