#include "Delay.h"

void StereoDelay::prepare(double sampleRate, int)
{
    currentSampleRate = sampleRate;
    delayBuffer.setSize(2, static_cast<int>(sampleRate * 3.0));
    delayBuffer.clear();
    writePosition = 0;
}

void StereoDelay::process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters)
{
    const auto mix = juce::jlimit(0.0f, 0.85f, parameters.delayMix.load());
    const auto feedback = juce::jlimit(0.0f, 0.88f, parameters.delayFeedback.load());
    const auto delaySamples = juce::jlimit(1, delayBuffer.getNumSamples() - 1, static_cast<int>(parameters.delayTime.load() * currentSampleRate));

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        const auto readPosition = (writePosition + delayBuffer.getNumSamples() - delaySamples) % delayBuffer.getNumSamples();
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            const auto input = buffer.getSample(channel, sample);
            const auto delayed = delayBuffer.getSample(channel, readPosition);
            delayBuffer.setSample(channel, writePosition, input + delayed * feedback);
            buffer.setSample(channel, sample, input * (1.0f - mix) + delayed * mix);
        }
        writePosition = (writePosition + 1) % delayBuffer.getNumSamples();
    }
}

void StereoDelay::reset()
{
    delayBuffer.clear();
    writePosition = 0;
}