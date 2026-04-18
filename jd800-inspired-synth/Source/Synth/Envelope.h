#pragma once

#include <JuceHeader.h>

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