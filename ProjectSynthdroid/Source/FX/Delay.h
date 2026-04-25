#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "../Synth/SynthParameters.h"

class StereoDelay
{
public:
    void prepare(double sampleRate, int maximumBlockSize);
    void process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters);
    void reset();

private:
    juce::AudioBuffer<float> delayBuffer;
    double currentSampleRate { 44100.0 };
    int writePosition { 0 };
};