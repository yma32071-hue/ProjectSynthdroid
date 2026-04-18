void PianoAcousticEngine::loadFromBinaryData()
{
    juce::WavAudioFormat format;

    auto numResources = BinaryData::namedResourceListSize;

    for (int i = 0; i < numResources; ++i)
    {
        const char* name = BinaryData::namedResourceList[i];
        int size = BinaryData::namedResourceListSize[i];

        juce::String resourceName(name);

        if (!resourceName.contains(".wav"))
            continue;

        // Example: SYNTH-60-2.wav
        auto parts = juce::StringArray::fromTokens(resourceName, "-", "");

        if (parts.size() < 3)
            continue;

        int note = parts[1].getIntValue();
        int layer = parts[2].upToLastOccurrenceOf(".wav", false, false).getIntValue();

        auto data = BinaryData::getNamedResource(name, size);

        juce::MemoryInputStream stream(data, (size_t)size, false);
        auto reader = format.createReaderFor(&stream, false);

        if (!reader)
            continue;

        Sample s;
        s.buffer.setSize((int)reader->numChannels,
                         (int)reader->lengthInSamples);

        reader->read(&s.buffer,
                     0,
                     (int)reader->lengthInSamples,
                     0,
                     true,
                     true);

        samples[note].resize(4);
        samples[note][layer] = std::move(s);
    }
}