#pragma once

#include <JuceHeader.h>
#include <array>
#include <atomic>

struct OscParameters
{
    std::atomic<float> waveform { 1.0f };
    std::atomic<float> level { 0.25f };
    std::atomic<float> octave { 0.0f };
    std::atomic<float> semitone { 0.0f };
    std::atomic<float> fine { 0.0f };
    std::atomic<float> pan { 0.0f };
};

struct SynthParameters
{
    std::array<OscParameters, 4> oscillators;
    std::atomic<float> masterGain { 0.72f };
    std::atomic<float> filterMode { 0.0f };
    std::atomic<float> filterSlope { 1.0f };
    std::atomic<float> cutoff { 7600.0f };
    std::atomic<float> resonance { 0.22f };
    std::atomic<float> filterEnvAmount { 4200.0f };
    std::atomic<float> ampAttack { 0.45f };
    std::atomic<float> ampDecay { 1.2f };
    std::atomic<float> ampSustain { 0.72f };
    std::atomic<float> ampRelease { 2.8f };
    std::atomic<float> filterAttack { 0.18f };
    std::atomic<float> filterDecay { 1.1f };
    std::atomic<float> filterSustain { 0.35f };
    std::atomic<float> filterRelease { 2.1f };
    std::atomic<float> lfo1Rate { 0.24f };
    std::atomic<float> lfo1PitchDepth { 0.08f };
    std::atomic<float> lfo2Rate { 0.17f };
    std::atomic<float> lfo2FilterDepth { 620.0f };
    std::atomic<float> chorusDepth { 0.34f };
    std::atomic<float> chorusRate { 0.26f };
    std::atomic<float> delayMix { 0.18f };
    std::atomic<float> delayTime { 0.37f };
    std::atomic<float> delayFeedback { 0.36f };
    std::atomic<float> reverbMix { 0.24f };
    std::atomic<float> reverbSize { 0.62f };
    std::atomic<float> crushAmount { 0.0f };
    std::atomic<bool> demoRiffEnabled { true };

    void loadWarmDigitalPad()
    {
        oscillators[0].waveform = 5.0f;
        oscillators[0].level = 0.34f;
        oscillators[0].octave = 0.0f;
        oscillators[0].fine = -3.0f;
        oscillators[0].pan = -0.35f;
        oscillators[1].waveform = 1.0f;
        oscillators[1].level = 0.25f;
        oscillators[1].octave = 0.0f;
        oscillators[1].fine = 4.0f;
        oscillators[1].pan = 0.35f;
        oscillators[2].waveform = 0.0f;
        oscillators[2].level = 0.18f;
        oscillators[2].octave = 1.0f;
        oscillators[2].fine = 1.0f;
        oscillators[2].pan = -0.15f;
        oscillators[3].waveform = 3.0f;
        oscillators[3].level = 0.13f;
        oscillators[3].octave = -1.0f;
        oscillators[3].fine = -2.0f;
        oscillators[3].pan = 0.15f;
        cutoff = 7600.0f;
        resonance = 0.22f;
        filterEnvAmount = 4200.0f;
        ampAttack = 0.45f;
        ampDecay = 1.2f;
        ampSustain = 0.72f;
        ampRelease = 2.8f;
        filterAttack = 0.18f;
        filterDecay = 1.1f;
        filterSustain = 0.35f;
        filterRelease = 2.1f;
        chorusDepth = 0.34f;
        delayMix = 0.18f;
        reverbMix = 0.24f;
    }
};