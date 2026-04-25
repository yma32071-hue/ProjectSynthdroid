#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

class SmoothEnvelope
{
public:
    void prepare(double sampleRate);
    void setParameters(float attack, float decay, float sustain, float release);
    void noteOn();
    void noteOff();
    float getNextSample();
    bool isActive() const;

private:
    juce::ADSR envelope;
    juce::ADSR::Parameters parameters;
};