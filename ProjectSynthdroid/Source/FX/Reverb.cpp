#include "Reverb.h"

void DigitalReverb::prepare(double sampleRate, int maximumBlockSize)
{
    reverb.prepare({ sampleRate, static_cast<juce::uint32>(maximumBlockSize), 2 });
}

void DigitalReverb::process(juce::AudioBuffer<float>& buffer, SynthParameters& parameters)
{
    juce::dsp::Reverb::Parameters p;
    p.roomSize = juce::jlimit(0.0f, 1.0f, parameters.reverbSize.load());
    p.damping = 0.42f;
    p.width = 0.92f;
    p.wetLevel = juce::jlimit(0.0f, 0.65f, parameters.reverbMix.load());
    p.dryLevel = 1.0f - p.wetLevel * 0.35f;
    p.freezeMode = 0.0f;
    reverb.setParameters(p);
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    reverb.process(context);
}