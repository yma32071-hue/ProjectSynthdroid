#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
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