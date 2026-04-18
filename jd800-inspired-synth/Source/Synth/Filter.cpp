#include "Filter.h"

void DigitalFilter::prepare(double sampleRate, int maximumBlockSize)
{
    juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32>(maximumBlockSize), 1 };
    filterLeft.prepare(spec);
    filterRight.prepare(spec);
}

void DigitalFilter::setMode(int mode)
{
    auto mapped = juce::dsp::StateVariableTPTFilterType::lowpass;
    if (mode == 1)
        mapped = juce::dsp::StateVariableTPTFilterType::highpass;
    else if (mode == 2)
        mapped = juce::dsp::StateVariableTPTFilterType::bandpass;
    filterLeft.setType(mapped);
    filterRight.setType(mapped);
}

void DigitalFilter::setCutoff(float cutoffHz)
{
    const auto safe = juce::jlimit(20.0f, 20000.0f, cutoffHz);
    filterLeft.setCutoffFrequency(safe);
    filterRight.setCutoffFrequency(safe);
}

void DigitalFilter::setResonance(float resonance)
{
    const auto q = juce::jlimit(0.08f, 0.98f, resonance);
    filterLeft.setResonance(q);
    filterRight.setResonance(q);
}

void DigitalFilter::reset()
{
    filterLeft.reset();
    filterRight.reset();
}

void DigitalFilter::process(float& left, float& right)
{
    left = filterLeft.processSample(0, left);
    right = filterRight.processSample(0, right);
}