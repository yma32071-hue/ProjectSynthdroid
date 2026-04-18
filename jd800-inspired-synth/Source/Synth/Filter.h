#pragma once

#include <JuceHeader.h>

class DigitalFilter
{
public:
    void prepare(double sampleRate, int maximumBlockSize);
    void setMode(int mode);
    void setCutoff(float cutoffHz);
    void setResonance(float resonance);
    void reset();
    void process(float& left, float& right);

private:
    juce::dsp::StateVariableTPTFilter<float> filterLeft;
    juce::dsp::StateVariableTPTFilter<float> filterRight;
};