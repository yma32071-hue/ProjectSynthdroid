#include "SynthEngine.h"

SynthEngine::SynthEngine()
{
    parameters.loadWarmDigitalPad();
    for (int i = 0; i < 16; ++i)
        synthesiser.addVoice(new DigitalSynthVoice(parameters));
    synthesiser.addSound(new DigitalSynthSound());
}

void SynthEngine::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    synthesiser.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synthesiser.getNumVoices(); ++i)
        if (auto* voice = dynamic_cast<DigitalSynthVoice*>(synthesiser.getVoice(i)))
            voice->prepare(sampleRate, samplesPerBlock);
    chorus.prepare(sampleRate, samplesPerBlock);
    delay.prepare(sampleRate, samplesPerBlock);
    reverb.prepare(sampleRate, samplesPerBlock);
}

void SynthEngine::renderNextBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    buffer.clear();
    addOriginalDemoRiff(midi, buffer.getNumSamples());
    synthesiser.renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
    chorus.process(buffer, parameters);
    delay.process(buffer, parameters);
    reverb.process(buffer, parameters);

    const auto crush = parameters.crushAmount.load();
    if (crush > 0.001f)
    {
        const auto steps = juce::jmap(crush, 65536.0f, 64.0f);
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                const auto v = buffer.getSample(channel, sample);
                buffer.setSample(channel, sample, std::round(v * steps) / steps);
            }
    }

    buffer.applyGain(0.85f);
    sampleCounter += buffer.getNumSamples();
}

SynthParameters& SynthEngine::getParameters()
{
    return parameters;
}

void SynthEngine::panic()
{
    synthesiser.allNotesOff(0, false);
    delay.reset();
}

void SynthEngine::addOriginalDemoRiff(juce::MidiBuffer& midi, int numSamples)
{
    if (! parameters.demoRiffEnabled.load())
        return;

    const std::array<int, 16> notes { 48, 55, 60, 64, 67, 72, 67, 64, 50, 57, 62, 65, 69, 74, 69, 65 };
    const auto stepSamples = static_cast<int64_t>(currentSampleRate * 0.34);
    const auto gateSamples = static_cast<int64_t>(currentSampleRate * 0.24);
    const auto blockStart = sampleCounter;
    const auto blockEnd = sampleCounter + numSamples;

    for (int offset = 0; offset < numSamples; ++offset)
    {
        const auto absoluteSample = blockStart + offset;
        if (absoluteSample % stepSamples == 0)
        {
            if (currentDemoNote >= 0)
                midi.addEvent(juce::MidiMessage::noteOff(1, currentDemoNote), offset);
            const auto index = static_cast<size_t>((absoluteSample / stepSamples) % notes.size());
            currentDemoNote = notes[index];
            midi.addEvent(juce::MidiMessage::noteOn(1, currentDemoNote, static_cast<juce::uint8>(82)), offset);
        }
        if (currentDemoNote >= 0 && absoluteSample % stepSamples == gateSamples)
        {
            midi.addEvent(juce::MidiMessage::noteOff(1, currentDemoNote), offset);
            currentDemoNote = -1;
        }
    }

    if (blockEnd < blockStart)
        currentDemoNote = -1;
}