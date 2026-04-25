#pragma once

#include "JuceIncludes.h"
#include "Synth/SynthEngine.h"

class MainComponent  : public juce::AudioAppComponent,
                       public juce::MidiKeyboardStateListener
{
public:
    MainComponent();
    ~MainComponent() override;

    // MIDI callbacks
    void handleNoteOn(juce::MidiKeyboardState* source,
                      int midiChannel,
                      int midiNoteNumber,
                      float velocity) override;

    void handleNoteOff(juce::MidiKeyboardState* source,
                       int midiChannel,
                       int midiNoteNumber,
                       float velocity) override;

    // Audio
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;

    // UI
    void resized() override;

private:
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard;

    SynthEngine synth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};