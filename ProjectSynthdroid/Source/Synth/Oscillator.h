#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

class DigitalOscillator
{
public:
    void prepare(double newSampleRate);
    float render(float waveform, float frequency);
    void reset();

private:
    double sampleRate { 44100.0 };
    float phase { 0.0f };
    juce::Random random;
    std::array<float, 2048> wavetable {};
};