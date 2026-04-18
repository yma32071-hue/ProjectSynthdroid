#pragma once

#include <JuceHeader.h>
#include "PianoKeyboard.h"

class MainView : public juce::Component
{
public:
    MainView();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    PianoKeyboard keyboard;

    juce::Slider volume;
};