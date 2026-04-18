#pragma once
#include <JuceHeader.h>

class PianoAcousticEngine
{
public:
    void loadSamples(const juce::File& folder);

    void noteOn(int note, float velocity);
    void noteOff(int note);

    void renderNextBlock(juce::AudioBuffer<float>& buffer);

private:
    struct Voice
    {
        juce::AudioBuffer<float> sample;
        int position = 0;
        bool active = false;
    };

    std::map<int, std::vector<Voice>> voices;

    std::set<int> held;
};