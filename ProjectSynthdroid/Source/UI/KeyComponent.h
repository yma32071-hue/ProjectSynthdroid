#pragma once
#include <JuceHeader.h>

class KeyComponent : public juce::Component
{
public:
    KeyComponent(int midiNote);

    void paint(juce::Graphics&) override;

    void setPressed(bool p);

    int getNote() const { return note; }

private:
    int note;
    bool pressed = false;
};