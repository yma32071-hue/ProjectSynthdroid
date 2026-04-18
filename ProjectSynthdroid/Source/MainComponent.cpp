#include "MainComponent.h"

MainComponent::MainComponent()
    : keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(keyboard);
    keyboardState.addListener(this);

    setAudioChannels(0, 2);
    setSize(800, 200);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int, double sampleRate)
{
    currentSampleRate = sampleRate;
}

void MainComponent::releaseResources() {}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* left = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* right = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

    for (int i = 0; i < bufferToFill.numSamples; ++i)
    {
        float sample = 0.0f;

        if (isPlaying)
        {
            sample = std::sin(angle) * level;
            angle += angleDelta;
        }

        left[i] = sample;
        right[i] = sample;
    }
}

void MainComponent::handleNoteOn(juce::MidiKeyboardState*, int, int midiNoteNumber, float velocity)
{
    auto frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

    angleDelta = frequency * 2.0 * juce::MathConstants<double>::pi / currentSampleRate;
    level = velocity * 0.25f;
    isPlaying = true;
}

void MainComponent::handleNoteOff(juce::MidiKeyboardState*, int, int, float)
{
    isPlaying = false;
}

void MainComponent::resized()
{
    keyboard.setBounds(getLocalBounds());
}