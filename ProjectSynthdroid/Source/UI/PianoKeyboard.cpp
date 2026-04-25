#include "PianoKeyboard.h"

PianoKeyboard::PianoKeyboard()
{
    setInterceptsMouseClicks(true, true);
}

void PianoKeyboard::setNoteCallback(std::function<void(int, float, bool)> cb)
{
    noteCallback = cb;
}

int PianoKeyboard::getNoteFromX(float x) const
{
    int key = (int)(x / keyWidth);
    return baseNote + key;
}

void PianoKeyboard::paint(juce::Graphics& g)
{
    auto w = getWidth();
    auto h = getHeight();

    g.fillAll(juce::Colour(15, 15, 20));

    for (int i = 0; i < numKeys; ++i)
    {
        float x = i * keyWidth;

        bool isBlack = (i % 7 == 1 || i % 7 == 3 || i % 7 == 6);

        juce::Colour c = isBlack
            ? juce::Colour(40, 40, 40)
            : juce::Colours::white;

        g.setColour(c);
        g.fillRoundedRectangle(x + 1, 1, keyWidth - 2, h - 2, 4.0f);

        if (isBlack)
        {
            g.setColour(juce::Colours::black.withAlpha(0.6f));
            g.drawRect((float)x, 0.0f, (float)keyWidth, (float)h);
        }
    }
}

void PianoKeyboard::mouseDown(const juce::MouseEvent& e)
{
    int note = getNoteFromX(e.position.x);
    int finger = e.source.getIndex();

    touches[finger] = { note, 1.0f };

    if (noteCallback)
        noteCallback(note, 1.0f, true);
}

void PianoKeyboard::mouseDrag(const juce::MouseEvent& e)
{
    int finger = e.source.getIndex();
    int note = getNoteFromX(e.position.x);

    if (touches[finger].note != note)
    {
        if (noteCallback)
        {
            noteCallback(touches[finger].note, 0.0f, false);
            noteCallback(note, 0.9f, true);
        }

        touches[finger].note = note;
    }
}

void PianoKeyboard::mouseUp(const juce::MouseEvent& e)
{
    int finger = e.source.getIndex();

    if (touches.count(finger))
    {
        if (noteCallback)
            noteCallback(touches[finger].note, 0.0f, false);

        touches.erase(finger);
    }
}