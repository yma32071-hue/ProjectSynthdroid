#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <map>
#include <vector>

class PianoAcousticEngine
{
public:
    void init();

    void noteOn(int note, float velocity);
    void noteOff(int note);

    void render(juce::AudioBuffer<float>& buffer);

private:
    struct Sample
    {
        juce::AudioBuffer<float> buffer;
        int position = 0;
        bool active = false;
    };

    // note → velocity layers
    std::map<int, std::vector<Sample>> samples;

    int getLayer(float velocity);
    void loadFromBinaryData();
};