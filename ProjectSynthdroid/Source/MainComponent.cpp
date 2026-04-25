#include "MainComponent.h"

MainComponent::MainComponent()
    : keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
    
{
    addAndMakeVisible(keyboard);


    keyboardState.addListener(this);
    
    setAudioChannels (0, 2);

    synth.init();

    setSize (800, 200);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::handleNoteOn(juce::MidiKeyboardState*,
                                int,
                                int note,
                                float velocity)
{
    synth.noteOn(note, velocity);
}

void MainComponent::handleNoteOff(juce::MidiKeyboardState*,
                                 int,
                                 int note,
                                 float)
{
    synth.noteOff(note);
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    synth.init(); // or synth.setSampleRate(sampleRate) if you have it
}

void MainComponent::releaseResources()
{
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    juce::MidiBuffer midi;

    keyboardState.processNextMidiBuffer(
        midi,
        bufferToFill.startSample,
        bufferToFill.numSamples,
        true);

    // =========================
    // CONNECT MIDI → ENGINE
    // =========================
    for (const auto metadata : midi)
    {
        const auto msg = metadata.getMessage();

        if (msg.isNoteOn())
            synth.noteOn(msg.getNoteNumber(), msg.getVelocity());

        else if (msg.isNoteOff())
            synth.noteOff(msg.getNoteNumber());
    }

    synth.render(*bufferToFill.buffer);
}

void MainComponent::resized()
{
    keyboard.setBounds (getLocalBounds());
}