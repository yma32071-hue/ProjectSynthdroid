#include "LookAndFeel.h"

WorkstationLookAndFeel::WorkstationLookAndFeel()
{
    setColour(juce::Slider::thumbColourId, juce::Colour(0xfff0d060));
    setColour(juce::Slider::trackColourId, juce::Colour(0xff42c4ff));
    setColour(juce::Slider::backgroundColourId, juce::Colour(0xff151927));
    setColour(juce::Label::textColourId, juce::Colours::white);
}

void WorkstationLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&)
{
    const auto bounds = juce::Rectangle<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)).reduced(4.0f);
    const auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.48f;
    const auto centre = bounds.getCentre();
    const auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    g.setColour(juce::Colour(0xff0a0d14));
    g.fillEllipse(bounds);
    g.setColour(juce::Colour(0xff4b5878));
    g.drawEllipse(bounds, 2.0f);
    juce::Path pointer;
    pointer.addRectangle(-2.0f, -radius, 4.0f, radius * 0.58f);
    g.setColour(juce::Colour(0xffffd76b));
    g.fillPath(pointer, juce::AffineTransform::rotation(angle).translated(centre.x, centre.y));
}

void WorkstationLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float, float, const juce::Slider::SliderStyle, juce::Slider&)
{
    auto bounds = juce::Rectangle<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)).reduced(6.0f, 2.0f);
    g.setColour(juce::Colour(0xff06080d));
    g.fillRoundedRectangle(bounds, 3.0f);
    g.setColour(juce::Colour(0xff24304d));
    g.drawRoundedRectangle(bounds, 3.0f, 1.0f);
    const auto thumb = juce::Rectangle<float>(bounds.getX(), sliderPos - 6.0f, bounds.getWidth(), 12.0f);
    g.setColour(juce::Colour(0xffffd76b));
    g.fillRoundedRectangle(thumb, 2.0f);
    g.setColour(juce::Colour(0xff141823));
    g.drawRoundedRectangle(thumb, 2.0f, 1.0f);
}