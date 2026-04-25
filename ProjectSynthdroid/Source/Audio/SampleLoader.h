#pragma once
#include "../JuceIncludes.h"

class SampleLoader
{
public:
    juce::AudioBuffer<float>* loadSample(const juce::String& name);

private:
    juce::AudioFormatManager formatManager;
};