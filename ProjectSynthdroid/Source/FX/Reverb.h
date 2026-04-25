#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "../Synth/SynthParameters.h"

class DigitalReverb
{
public:
    void prepare(double sampleRate, int maximumBlockSize);
    void process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters);

private:
    juce::dsp::Reverb reverb;
};