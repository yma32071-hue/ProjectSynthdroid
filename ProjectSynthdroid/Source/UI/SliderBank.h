#pragma once

#include <JuceHeader.h>
#include <functional>

class SliderBank final : public juce::Component
{
public:
    struct Control
    {
        juce::String name;
        float min;
        float max;
        float value;
        std::function<void(float)> onChange;
    };

    void setTitle(const juce::String& newTitle);
    void addControl(const Control& control);
    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    struct SliderItem
    {
        juce::Slider slider;
        juce::Label label;
    };

    juce::String title;
    std::vector<std::unique_ptr<SliderItem>> items;
};