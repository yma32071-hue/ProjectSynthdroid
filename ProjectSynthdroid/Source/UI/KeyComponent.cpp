#include "KeyComponent.h"

KeyComponent::KeyComponent(int midiNote)
    : note(midiNote)
{
}

void KeyComponent::setPressed(bool p)
{
    pressed = p;
    repaint();
}

void KeyComponent::paint(juce::Graphics& g)
{
    auto area = getLocalBounds().toFloat();

    juce::Colour base = (note % 12 == 1 || note % 12 == 3 || note % 12 == 6)
        ? juce::Colour(40, 40, 40)
        : juce::Colours::white;

    if (pressed)
        base = juce::Colours::orange;

    g.setColour(base);
    g.fillRoundedRectangle(area, 4.0f);

    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.drawRoundedRectangle(area, 4.0f, 1.0f);
}