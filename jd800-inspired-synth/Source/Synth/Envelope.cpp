#include "Envelope.h"

void SmoothEnvelope::prepare(double sampleRate)
{
    envelope.setSampleRate(sampleRate);
}

void SmoothEnvelope::setParameters(float attack, float decay, float sustain, float release)
{
    parameters.attack = juce::jlimit(0.001f, 10.0f, attack);
    parameters.decay = juce::jlimit(0.001f, 10.0f, decay);
    parameters.sustain = juce::jlimit(0.0f, 1.0f, sustain);
    parameters.release = juce::jlimit(0.001f, 12.0f, release);
    envelope.setParameters(parameters);
}

void SmoothEnvelope::noteOn()
{
    envelope.noteOn();
}

void SmoothEnvelope::noteOff()
{
    envelope.noteOff();
}

float SmoothEnvelope::getNextSample()
{
    return envelope.getNextSample();
}

bool SmoothEnvelope::isActive() const
{
    return envelope.isActive();
}