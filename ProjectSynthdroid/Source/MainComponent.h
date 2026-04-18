#pragma once
#include <JuceHeader.h>
#include "PianoAcousticEngine.h"
#include "PianoVisualEngine.h"
#include "TouchController.h"

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override = default;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    PianoAcousticEngine engine;
    PianoVisualEngine visual;
    std::unique_ptr<TouchController> touch;

    juce::AudioFormatManager formatManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};