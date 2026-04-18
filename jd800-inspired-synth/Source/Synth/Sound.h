#pragma once

#include <JuceHeader.h>

class DigitalSynthSound final : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int) override;
    bool appliesToChannel(int) override;
};