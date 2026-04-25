#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

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