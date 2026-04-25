#include "SynthEngine.h"

void SynthEngine::init()
{
    voices.resize(8); // 8 voice polyphony

    // load a sample (make sure this exists in SampleLoader)
    auto* sample = loader.loadSample("piano.wav");

    for (auto& v : voices)
        v.sample = sample;
}

void SynthEngine::noteOn(int note, float velocity)
{
    for (auto& v : voices)
    {
        if (!v.active)
        {
            v.position = 0;
            v.active = true;
            return;
        }
    }
}

void SynthEngine::noteOff(int midiNote)
{
    // simple version: stop all voices
    for (auto& v : voices)
        v.active = false;
}

void SynthEngine::render(juce::AudioBuffer<float>& buffer)
{
    buffer.clear();

    for (auto& v : voices)
    {
        if (!v.active || v.sample == nullptr)
            continue;

        auto* sampleData = v.sample->getReadPointer(0);
        auto* outL = buffer.getWritePointer(0);
        auto* outR = buffer.getNumChannels() > 1 ? buffer.getWritePointer(1) : nullptr;

        int numSamples = buffer.getNumSamples();
        int sampleLength = v.sample->getNumSamples();

        for (int i = 0; i < numSamples; ++i)
        {
            if (v.position >= sampleLength)
            {
                v.active = false;
                break;
            }

            float s = sampleData[v.position++];

            outL[i] += s;
            if (outR) outR[i] += s;
        }
    }
}