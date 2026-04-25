#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

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