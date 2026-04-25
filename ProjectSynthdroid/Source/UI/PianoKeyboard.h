#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <map>
#include <functional>

class PianoKeyboard : public juce::Component
{
public:
    PianoKeyboard();
    ~PianoKeyboard() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;

    void setNoteCallback(std::function<void(int note, float velocity, bool on)> cb);

private:
    int getNoteFromX(float x) const;

    struct TouchState
    {
        int note = -1;
        float velocity = 1.0f;
    };

    std::map<int, TouchState> touches;

    std::function<void(int, float, bool)> noteCallback;

    int baseNote = 60;
    int numKeys = 48;

    float keyWidth = 40.0f;
};