#include "MainComponent.h"

/// =======================
/// SIMPLE SINE WAVE VOICE
/// =======================
class SineVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound*) override { return true; }

    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int) override
    {
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity * 0.2f;
        angle = 0.0;
        angleDelta = frequency * 2.0 * juce::MathConstants<double>::pi / getSampleRate();
    }

    void stopNote (float, bool allowTailOff) override
    {
        clearCurrentNote();
    }

    void pitchWheelMoved (int) override {}
    void controllerMoved (int, int) override {}

    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                          int startSample,
                          int numSamples) override
    {
        for (int i = 0; i < numSamples; ++i)
        {
            float sample = std::sin(angle) * level;
            angle += angleDelta;

            for (int ch = 0; ch < outputBuffer.getNumChannels(); ++ch)
                outputBuffer.addSample(ch, startSample + i, sample);
        }
    }

private:
    double frequency = 440.0;
    double angle = 0.0;
    double angleDelta = 0.0;
    float level = 0.0f;
};

/// =======================
/// EMPTY SOUND
/// =======================
class SineSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int) override { return true; }
    bool appliesToChannel (int) override { return true; }
};

/// =======================
/// MAIN COMPONENT
/// =======================
MainComponent::MainComponent()
    : keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(keyboard);

    setAudioChannels(0, 2);

    // synth setup
    synth.clearSounds();
    synth.clearVoices();

    synth.addSound(new SineSound());

    for (int i = 0; i < 8; ++i)
        synth.addVoice(new SineVoice());

    setSize(800, 200);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void MainComponent::releaseResources() {}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    juce::MidiBuffer midi;

    keyboardState.processNextMidiBuffer(midi,
                                        bufferToFill.startSample,
                                        bufferToFill.numSamples,
                                        true);

    synth.renderNextBlock(*bufferToFill.buffer,
                          midi,
                          bufferToFill.startSample,
                          bufferToFill.numSamples);
}

void MainComponent::resized()
{
    keyboard.setBounds(getLocalBounds());
}