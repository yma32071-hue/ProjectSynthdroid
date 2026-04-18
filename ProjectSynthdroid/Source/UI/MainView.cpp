#include "MainView.h"

MainView::MainView()
{
    addAndMakeVisible(keyboard);

    keyboard.setNoteCallback(
        [](int note, float vel, bool on)
        {
            // connect to SynthEngine here
        });

    volume.setRange(0.0, 1.0);
    addAndMakeVisible(volume);
}

void MainView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(10, 10, 15));
}

void MainView::resized()
{
    auto area = getLocalBounds();

    volume.setBounds(area.removeFromBottom(40));
    keyboard.setBounds(area);
}