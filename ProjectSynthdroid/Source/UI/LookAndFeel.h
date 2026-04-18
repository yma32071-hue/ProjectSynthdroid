#pragma once

#include <JuceHeader.h>

class WorkstationLookAndFeel final : public juce::LookAndFeel_V4
{
public:
    WorkstationLookAndFeel();
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider) override;
};