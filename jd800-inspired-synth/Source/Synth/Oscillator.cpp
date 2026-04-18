#include "Oscillator.h"

void DigitalOscillator::prepare(double newSampleRate)
{
    sampleRate = newSampleRate;
    for (size_t i = 0; i < wavetable.size(); ++i)
    {
        const auto p = juce::MathConstants<float>::twoPi * static_cast<float>(i) / static_cast<float>(wavetable.size());
        wavetable[i] = 0.52f * std::sin(p) + 0.23f * std::sin(2.0f * p + 0.7f) + 0.13f * std::sin(5.0f * p);
    }
}

float DigitalOscillator::render(float waveform, float frequency)
{
    const auto index = static_cast<int>(std::round(waveform));
    float sample = 0.0f;

    if (index == 0)
        sample = std::sin(juce::MathConstants<float>::twoPi * phase);
    else if (index == 1)
        sample = 2.0f * phase - 1.0f;
    else if (index == 2)
        sample = phase < 0.5f ? 1.0f : -1.0f;
    else if (index == 3)
        sample = 1.0f - 4.0f * std::abs(phase - 0.5f);
    else if (index == 4)
        sample = random.nextFloat() * 2.0f - 1.0f;
    else
    {
        const auto tablePosition = phase * static_cast<float>(wavetable.size());
        const auto i0 = static_cast<size_t>(tablePosition) % wavetable.size();
        const auto i1 = (i0 + 1) % wavetable.size();
        const auto frac = tablePosition - std::floor(tablePosition);
        sample = juce::jmap(frac, wavetable[i0], wavetable[i1]);
    }

    phase += static_cast<float>(frequency / sampleRate);
    while (phase >= 1.0f)
        phase -= 1.0f;

    return sample;
}

void DigitalOscillator::reset()
{
    phase = 0.0f;
}