#pragma once
#include <JuceHeader.h>

class MainComponent : public juce::AudioAppComponent,
                      public juce::MidiKeyboardStateListener
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay (int, double) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo&) override;
    void releaseResources() override;

    void resized() override;

    // MIDI callbacks
    void handleNoteOn(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(juce::MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

private:
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard;

    // simple synth state
    double currentSampleRate = 44100.0;
    double angle = 0.0;
    double angleDelta = 0.0;
    float level = 0.0f;
    bool isPlaying = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};