#include "Voice.h"
#include "Sound.h"

DigitalSynthVoice::DigitalSynthVoice(SynthParameters& parameters) : params(parameters)
{
}

void DigitalSynthVoice::prepare(double sampleRate, int maximumBlockSize)
{
    currentSampleRate = sampleRate;
    for (auto& osc : oscillators)
        osc.prepare(sampleRate);
    ampEnvelope.prepare(sampleRate);
    filterEnvelope.prepare(sampleRate);
    lfo1.prepare(sampleRate);
    lfo2.prepare(sampleRate);
    filter.prepare(sampleRate, maximumBlockSize);
}

bool DigitalSynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<DigitalSynthSound*>(sound) != nullptr;
}

void DigitalSynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    noteFrequency = static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    noteVelocity = velocity;
    pitchBendSemitones = 0.0f;
    for (auto& osc : oscillators)
        osc.reset();
    lfo1.reset();
    lfo2.reset();
    filter.reset();
    ampEnvelope.setParameters(params.ampAttack, params.ampDecay, params.ampSustain, params.ampRelease);
    filterEnvelope.setParameters(params.filterAttack, params.filterDecay, params.filterSustain, params.filterRelease);
    ampEnvelope.noteOn();
    filterEnvelope.noteOn();
}

void DigitalSynthVoice::stopNote(float, bool allowTailOff)
{
    ampEnvelope.noteOff();
    filterEnvelope.noteOff();
    if (! allowTailOff)
        clearCurrentNote();
}

void DigitalSynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
    const auto normalised = (static_cast<float>(newPitchWheelValue) - 8192.0f) / 8192.0f;
    pitchBendSemitones = normalised * 2.0f;
}

void DigitalSynthVoice::controllerMoved(int, int)
{
}

void DigitalSynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (! isVoiceActive())
        return;

    lfo1.setRate(params.lfo1Rate);
    lfo2.setRate(params.lfo2Rate);
    lfo1.setWaveform(0);
    lfo2.setWaveform(1);
    filter.setMode(static_cast<int>(params.filterMode.load()));
    filter.setResonance(params.resonance);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        const auto amp = ampEnvelope.getNextSample();
        const auto filterEnv = filterEnvelope.getNextSample();
        const auto lfoPitch = lfo1.render() * params.lfo1PitchDepth.load();
        const auto lfoFilter = lfo2.render() * params.lfo2FilterDepth.load();
        const auto baseFrequency = noteFrequency * std::pow(2.0f, (pitchBendSemitones + lfoPitch) / 12.0f);
        float left = 0.0f;
        float right = 0.0f;

        for (size_t i = 0; i < oscillators.size(); ++i)
        {
            const auto& oscParams = params.oscillators[i];
            const auto transpose = oscParams.octave.load() * 12.0f + oscParams.semitone.load() + oscParams.fine.load() * 0.01f;
            const auto frequency = baseFrequency * std::pow(2.0f, transpose / 12.0f);
            const auto raw = oscillators[i].render(oscParams.waveform.load(), frequency) * oscParams.level.load();
            const auto pan = juce::jlimit(-1.0f, 1.0f, oscParams.pan.load());
            const auto gainLeft = std::sqrt(0.5f * (1.0f - pan));
            const auto gainRight = std::sqrt(0.5f * (1.0f + pan));
            left += raw * gainLeft;
            right += raw * gainRight;
        }

        const auto cutoff = params.cutoff.load() + filterEnv * params.filterEnvAmount.load() + lfoFilter;
        filter.setCutoff(cutoff);
        filter.process(left, right);
        left *= amp * noteVelocity * params.masterGain.load();
        right *= amp * noteVelocity * params.masterGain.load();

        outputBuffer.addSample(0, startSample + sample, left);
        outputBuffer.addSample(1, startSample + sample, right);
    }

    if (! ampEnvelope.isActive())
        clearCurrentNote();
}