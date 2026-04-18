#include "PianoAcousticEngine.h"

void PianoAcousticEngine::loadSamples(const juce::File& folder)
{
    juce::AudioFormatManager fm;
    fm.registerBasicFormats();

    for (int note = 48; note < 72; ++note)
    {
        std::vector<Voice> v;

        for (int i = 0; i < 1; ++i)
        {
            auto file = folder.getChildFile(juce::String(note) + ".wav");

            std::unique_ptr<juce::AudioFormatReader> reader(fm.createReaderFor(file));

            if (reader)
            {
                Voice voice;
                voice.sample.setSize((int)reader->numChannels,
                                     (int)reader->lengthInSamples);

                reader->read(&voice.sample, 0, (int)reader->lengthInSamples, 0, true, true);

                v.push_back(std::move(voice));
            }
        }

        voices[note] = v;
    }
}

void PianoAcousticEngine::noteOn(int note, float)
{
    for (auto& v : voices[note])
    {
        v.position = 0;
        v.active = true;
    }

    held.insert(note);
}

void PianoAcousticEngine::noteOff(int note)
{
    held.erase(note);
}

void PianoAcousticEngine::renderNextBlock(juce::AudioBuffer<float>& buffer)
{
    buffer.clear();

    for (auto& [note, vlist] : voices)
    {
        for (auto& v : vlist)
        {
            if (!v.active) continue;

            for (int i = 0; i < buffer.getNumSamples(); ++i)
            {
                if (v.position >= v.sample.getNumSamples())
                {
                    v.active = false;
                    break;
                }

                for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
                {
                    buffer.addSample(ch, i,
                        v.sample.getSample(ch % v.sample.getNumChannels(), v.position) * 0.5f);
                }

                v.position++;
            }
        }
    }
}