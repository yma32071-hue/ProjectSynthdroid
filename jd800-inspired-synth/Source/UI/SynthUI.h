#pragma once

#include <JuceHeader.h>
#include "SliderBank.h"
#include "LookAndFeel.h"
#include "../Synth/SynthParameters.h"

class SynthUI final : public juce::Component
{
public:
    explicit SynthUI(SynthParameters& parameters);
    ~SynthUI() override;
    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    SynthParameters& params;
    WorkstationLookAndFeel lookAndFeel;
    SliderBank oscBank;
    SliderBank filterBank;
    SliderBank ampBank;
    SliderBank filterEnvBank;
    SliderBank lfoBank;
    SliderBank effectsBank;
    juce::TextButton demoButton { "Original Demo Riff" };
    juce::TextButton panicButton { "Panic" };
    std::function<void()> panicCallback;

public:
    void setPanicCallback(std::function<void()> callback);
};