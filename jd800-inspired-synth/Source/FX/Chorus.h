#pragma once

#include <JuceHeader.h>
#include "../Synth/SynthParameters.h"

class WideChorus
{
public:
    void prepare(double sampleRate, int maximumBlockSize);
    void process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters);

private:
    juce::dsp::Chorus<float> chorus;
};