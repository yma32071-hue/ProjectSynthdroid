#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

class DigitalSynthSound final : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int) override;
    bool appliesToChannel(int) override;
};