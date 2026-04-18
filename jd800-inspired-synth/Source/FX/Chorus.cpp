#include "Chorus.h"

void WideChorus::prepare(double sampleRate, int maximumBlockSize)
{
    chorus.prepare({ sampleRate, static_cast<juce::uint32>(maximumBlockSize), 2 });
}

void WideChorus::process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters)
{
    chorus.setRate(parameters.chorusRate.load());
    chorus.setDepth(parameters.chorusDepth.load());
    chorus.setCentreDelay(8.0f);
    chorus.setFeedback(0.12f);
    chorus.setMix(juce::jlimit(0.0f, 0.65f, parameters.chorusDepth.load()));
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    chorus.process(context);
}