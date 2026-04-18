#include "LFO.h"

void VoiceLFO::prepare(double newSampleRate)
{
    sampleRate = newSampleRate;
}

void VoiceLFO::setRate(float rateHz)
{
    rate = juce::jlimit(0.01f, 30.0f, rateHz);
}

void VoiceLFO::setWaveform(int waveform)
{
    waveformType = waveform;
}

float VoiceLFO::render()
{
    float output = 0.0f;
    if (waveformType == 0)
        output = std::sin(juce::MathConstants<float>::twoPi * phase);
    else if (waveformType == 1)
        output = 1.0f - 4.0f * std::abs(phase - 0.5f);
    else if (waveformType == 2)
        output = phase < 0.5f ? 1.0f : -1.0f;
    else
        output = randomValue;

    const auto previousPhase = phase;
    phase += static_cast<float>(rate / sampleRate);
    if (phase >= 1.0f)
    {
        phase -= 1.0f;
        if (waveformType == 3 || previousPhase > phase)
            randomValue = random.nextFloat() * 2.0f - 1.0f;
    }

    return output;
}

void VoiceLFO::reset()
{
    phase = 0.0f;
}