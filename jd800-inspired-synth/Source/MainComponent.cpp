#include "MainComponent.h"

MainComponent::MainComponent() : synthUI(engine.getParameters())
{
    setSize(1180, 720);
    addAndMakeVisible(synthUI);
    addAndMakeVisible(keyboard);
    synthUI.setPanicCallback([this] { engine.panic(); keyboardState.allNotesOff(0); });

    auto devices = juce::MidiInput::getAvailableDevices();
    if (! devices.isEmpty())
    {
        midiInput = juce::MidiInput::openDevice(devices[0].identifier, this);
        if (midiInput)
            midiInput->start();
    }

    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
    if (midiInput)
        midiInput->stop();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    midiCollector.reset(sampleRate);
    engine.prepareToPlay(sampleRate, samplesPerBlockExpected);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    juce::MidiBuffer midi;
    midiCollector.removeNextBlockOfMessages(midi, bufferToFill.numSamples);
    keyboardState.processNextMidiBuffer(midi, 0, bufferToFill.numSamples, true);
    engine.renderNextBlock(*bufferToFill.buffer, midi);
}

void MainComponent::releaseResources()
{
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    keyboard.setBounds(area.removeFromBottom(86).reduced(10));
    synthUI.setBounds(area);
}

void MainComponent::handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
{
    midiCollector.addMessageToQueue(message);
}