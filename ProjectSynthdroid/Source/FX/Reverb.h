#pragma once

#include <JuceHeader.h>
#include "../Synth/SynthParameters.h"

class DigitalReverb
{
public:
    void prepare(double sampleRate, int maximumBlockSize);
    void process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters);

private:
    juce::dsp::Reverb reverb;
};