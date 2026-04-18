#pragma once

#include <JuceHeader.h>
#include "Synth/SynthEngine.h"
#include "UI/SynthUI.h"

class MainComponent final : public juce::AudioAppComponent,
                            private juce::MidiInputCallback
{
public:
    MainComponent();
    ~MainComponent() override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void resized() override;

private:
    void handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message) override;
    SynthEngine engine;
    SynthUI synthUI;
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard { keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };
    juce::MidiMessageCollector midiCollector;
    std::unique_ptr<juce::MidiInput> midiInput;
};