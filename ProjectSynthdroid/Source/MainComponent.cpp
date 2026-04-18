#include "MainComponent.h"

MainComponent::MainComponent()
{
    setAudioChannels(0, 2); // Android-safe stereo output

    formatManager.registerBasicFormats();

    touch = std::make_unique<TouchController>(engine, visual);

    addAndMakeVisible(visual);
}

void MainComponent::prepareToPlay(int, double)
{
    // Load samples from APK/assets folder OR filesystem
    engine.loadSamples(juce::File("samples/piano"));
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    // ⚠️ This is simplified placeholder mixing
    // In real build you'd stream samples or use AudioSourcePlayer

    // (kept minimal for clarity)
}

void MainComponent::releaseResources()
{
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(10, 10, 15));
}

void MainComponent::resized()
{
    visual.setBounds(getLocalBounds());
}