#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "Oscillator.h"
#include "Envelope.h"
#include "LFO.h"
#include "Filter.h"
#include "SynthParameters.h"

class DigitalSynthVoice final : public juce::SynthesiserVoice
{
public:
    explicit DigitalSynthVoice(SynthParameters& parameters);
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void prepare(double sampleRate, int maximumBlockSize);

private:
    SynthParameters& params;
    std::array<DigitalOscillator, 4> oscillators;
    SmoothEnvelope ampEnvelope;
    SmoothEnvelope filterEnvelope;
    VoiceLFO lfo1;
    VoiceLFO lfo2;
    DigitalFilter filter;
    double currentSampleRate { 44100.0 };
    float noteFrequency { 440.0f };
    float noteVelocity { 0.0f };
    float pitchBendSemitones { 0.0f };
};