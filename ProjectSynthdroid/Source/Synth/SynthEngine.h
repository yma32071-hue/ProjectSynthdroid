#pragma once

#include <JuceHeader.h>
#include "SynthParameters.h"
#include "Voice.h"
#include "Sound.h"
#include "../FX/Chorus.h"
#include "../FX/Delay.h"
#include "../FX/Reverb.h"

class SynthEngine
{
public:
    SynthEngine();
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void renderNextBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi);
    SynthParameters& getParameters();
    void panic();

private:
    void addOriginalDemoRiff(juce::MidiBuffer& midi, int numSamples);
    juce::Synthesiser synthesiser;
    SynthParameters parameters;
    WideChorus chorus;
    StereoDelay delay;
    DigitalReverb reverb;
    double currentSampleRate { 44100.0 };
    int64_t sampleCounter { 0 };
    int currentDemoNote { -1 };
};