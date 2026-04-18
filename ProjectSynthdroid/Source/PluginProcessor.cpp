#include "PluginProcessor.h"

DigitalWorkstationPluginProcessor::DigitalWorkstationPluginProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

const juce::String DigitalWorkstationPluginProcessor::getName() const
{
    return "Digital Workstation Synth";
}

void DigitalWorkstationPluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    engine.prepareToPlay(sampleRate, samplesPerBlock);
}

void DigitalWorkstationPluginProcessor::releaseResources()
{
}

bool DigitalWorkstationPluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void DigitalWorkstationPluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    engine.renderNextBlock(buffer, midi);
}

juce::AudioProcessorEditor* DigitalWorkstationPluginProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

bool DigitalWorkstationPluginProcessor::hasEditor() const
{
    return true;
}

double DigitalWorkstationPluginProcessor::getTailLengthSeconds() const
{
    return 4.0;
}

int DigitalWorkstationPluginProcessor::getNumPrograms()
{
    return 1;
}

int DigitalWorkstationPluginProcessor::getCurrentProgram()
{
    return 0;
}

void DigitalWorkstationPluginProcessor::setCurrentProgram(int)
{
}

const juce::String DigitalWorkstationPluginProcessor::getProgramName(int)
{
    return "Warm Digital Pad";
}

void DigitalWorkstationPluginProcessor::changeProgramName(int, const juce::String&)
{
}

void DigitalWorkstationPluginProcessor::getStateInformation(juce::MemoryBlock&)
{
}

void DigitalWorkstationPluginProcessor::setStateInformation(const void*, int)
{
}

bool DigitalWorkstationPluginProcessor::acceptsMidi() const
{
    return true;
}

bool DigitalWorkstationPluginProcessor::producesMidi() const
{
    return false;
}

bool DigitalWorkstationPluginProcessor::isMidiEffect() const
{
    return false;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DigitalWorkstationPluginProcessor();
}