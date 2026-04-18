#include "SliderBank.h"

void SliderBank::setTitle(const juce::String& newTitle)
{
    title = newTitle;
    repaint();
}

void SliderBank::addControl(const Control& control)
{
    auto item = std::make_unique<SliderItem>();
    item->slider.setSliderStyle(juce::Slider::LinearVertical);
    item->slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 58, 18);
    item->slider.setRange(control.min, control.max, 0.001);
    item->slider.setValue(control.value, juce::dontSendNotification);
    item->slider.onValueChange = [slider = &item->slider, callback = control.onChange] { callback(static_cast<float>(slider->getValue())); };
    item->label.setText(control.name, juce::dontSendNotification);
    item->label.setJustificationType(juce::Justification::centred);
    item->label.setFont(juce::FontOptions(11.0f, juce::Font::bold));
    addAndMakeVisible(item->slider);
    addAndMakeVisible(item->label);
    items.push_back(std::move(item));
}

void SliderBank::resized()
{
    auto area = getLocalBounds().reduced(8);
    area.removeFromTop(22);
    if (items.empty())
        return;

    const auto width = juce::jmax(42, area.getWidth() / static_cast<int>(items.size()));
    for (auto& item : items)
    {
        auto column = area.removeFromLeft(width).reduced(2, 0);
        item->label.setBounds(column.removeFromTop(20));
        item->slider.setBounds(column);
    }
}

void SliderBank::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);
    g.setColour(juce::Colour(0xff101626));
    g.fillRoundedRectangle(bounds, 7.0f);
    g.setColour(juce::Colour(0xff394564));
    g.drawRoundedRectangle(bounds, 7.0f, 1.0f);
    g.setColour(juce::Colour(0xffa6c9ff));
    g.setFont(juce::FontOptions(13.0f, juce::Font::bold));
    g.drawText(title, getLocalBounds().removeFromTop(24), juce::Justification::centred);
}