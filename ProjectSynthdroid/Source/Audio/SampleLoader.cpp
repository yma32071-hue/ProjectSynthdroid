#include "SampleLoader.h"

juce::AudioBuffer<float>* SampleLoader::loadSample(const juce::String& name)
{
    formatManager.registerBasicFormats();

    auto file = juce::File::getCurrentWorkingDirectory().getChildFile(name);

    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    if (reader.get() == nullptr)
        return nullptr;

    auto* buffer = new juce::AudioBuffer<float>(reader->numChannels, reader->lengthInSamples);
    reader->read(buffer, 0, reader->lengthInSamples, 0, true, true);

    return buffer;
}