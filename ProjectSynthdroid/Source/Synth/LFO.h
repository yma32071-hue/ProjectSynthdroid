#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

class VoiceLFO
{
public:
    void prepare(double sampleRate);
    void setRate(float rateHz);
    void setWaveform(int waveform);
    float render();
    void reset();

private:
    double sampleRate { 44100.0 };
    float phase { 0.0f };
    float rate { 1.0f };
    int waveformType { 0 };
    juce::Random random;
    float randomValue { 0.0f };
};