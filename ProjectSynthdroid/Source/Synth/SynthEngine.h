#pragma once
#include "../JuceIncludes.h"
#include "../Audio/SampleLoader.h"

class SynthEngine
{
public:
    void init();
    void noteOn(int note, float velocity);
    void noteOff(int midiNote);
    void render(juce::AudioBuffer<float>& buffer);

private:
    struct Voice
    {
        juce::AudioBuffer<float>* sample = nullptr;
        int position = 0;
        bool active = false;
    };

    std::vector<Voice> voices;
    SampleLoader loader;
};