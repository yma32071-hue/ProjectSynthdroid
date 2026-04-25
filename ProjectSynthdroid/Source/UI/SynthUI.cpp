#include "SynthUI.h"

SynthUI::SynthUI(SynthParameters& parameters) : params(parameters)
{
    setLookAndFeel(&lookAndFeel);

    oscBank.setTitle("PARTIAL OSCILLATORS");
    for (size_t i = 0; i < params.oscillators.size(); ++i)
    {
        const auto label = juce::String("W") + juce::String(static_cast<int>(i + 1));
        oscBank.addControl({ label, 0.0f, 5.0f, params.oscillators[i].waveform.load(), [this, i](float v) { params.oscillators[i].waveform = v; } });
        oscBank.addControl({ juce::String("L") + juce::String(static_cast<int>(i + 1)), 0.0f, 0.8f, params.oscillators[i].level.load(), [this, i](float v) { params.oscillators[i].level = v; } });
        oscBank.addControl({ juce::String("F") + juce::String(static_cast<int>(i + 1)), -24.0f, 24.0f, params.oscillators[i].fine.load(), [this, i](float v) { params.oscillators[i].fine = v; } });
        oscBank.addControl({ juce::String("P") + juce::String(static_cast<int>(i + 1)), -1.0f, 1.0f, params.oscillators[i].pan.load(), [this, i](float v) { params.oscillators[i].pan = v; } });
    }

    filterBank.setTitle("DIGITAL TVF");
    filterBank.addControl({ "MODE", 0.0f, 2.0f, params.filterMode.load(), [this](float v) { params.filterMode = std::round(v); } });
    filterBank.addControl({ "CUT", 20.0f, 20000.0f, params.cutoff.load(), [this](float v) { params.cutoff = v; } });
    filterBank.addControl({ "RES", 0.08f, 0.98f, params.resonance.load(), [this](float v) { params.resonance = v; } });
    filterBank.addControl({ "ENV", -9000.0f, 9000.0f, params.filterEnvAmount.load(), [this](float v) { params.filterEnvAmount = v; } });

    ampBank.setTitle("AMPLIFIER ENV");
    ampBank.addControl({ "A", 0.001f, 6.0f, params.ampAttack.load(), [this](float v) { params.ampAttack = v; } });
    ampBank.addControl({ "D", 0.001f, 6.0f, params.ampDecay.load(), [this](float v) { params.ampDecay = v; } });
    ampBank.addControl({ "S", 0.0f, 1.0f, params.ampSustain.load(), [this](float v) { params.ampSustain = v; } });
    ampBank.addControl({ "R", 0.001f, 10.0f, params.ampRelease.load(), [this](float v) { params.ampRelease = v; } });

    filterEnvBank.setTitle("FILTER ENV");
    filterEnvBank.addControl({ "A", 0.001f, 6.0f, params.filterAttack.load(), [this](float v) { params.filterAttack = v; } });
    filterEnvBank.addControl({ "D", 0.001f, 6.0f, params.filterDecay.load(), [this](float v) { params.filterDecay = v; } });
    filterEnvBank.addControl({ "S", 0.0f, 1.0f, params.filterSustain.load(), [this](float v) { params.filterSustain = v; } });
    filterEnvBank.addControl({ "R", 0.001f, 10.0f, params.filterRelease.load(), [this](float v) { params.filterRelease = v; } });

    lfoBank.setTitle("MODULATION");
    lfoBank.addControl({ "LFO1", 0.01f, 12.0f, params.lfo1Rate.load(), [this](float v) { params.lfo1Rate = v; } });
    lfoBank.addControl({ "PITCH", 0.0f, 1.2f, params.lfo1PitchDepth.load(), [this](float v) { params.lfo1PitchDepth = v; } });
    lfoBank.addControl({ "LFO2", 0.01f, 12.0f, params.lfo2Rate.load(), [this](float v) { params.lfo2Rate = v; } });
    lfoBank.addControl({ "TVF", 0.0f, 5000.0f, params.lfo2FilterDepth.load(), [this](float v) { params.lfo2FilterDepth = v; } });

    effectsBank.setTitle("EFFECTS");
    effectsBank.addControl({ "CHO", 0.0f, 0.65f, params.chorusDepth.load(), [this](float v) { params.chorusDepth = v; } });
    effectsBank.addControl({ "DLY", 0.0f, 0.85f, params.delayMix.load(), [this](float v) { params.delayMix = v; } });
    effectsBank.addControl({ "TIME", 0.05f, 1.4f, params.delayTime.load(), [this](float v) { params.delayTime = v; } });
    effectsBank.addControl({ "FDBK", 0.0f, 0.88f, params.delayFeedback.load(), [this](float v) { params.delayFeedback = v; } });
    effectsBank.addControl({ "REV", 0.0f, 0.65f, params.reverbMix.load(), [this](float v) { params.reverbMix = v; } });
    effectsBank.addControl({ "CRSH", 0.0f, 1.0f, params.crushAmount.load(), [this](float v) { params.crushAmount = v; } });

    demoButton.setClickingTogglesState(true);
    demoButton.setToggleState(params.demoRiffEnabled.load(), juce::dontSendNotification);
    demoButton.onClick = [this] { params.demoRiffEnabled = demoButton.getToggleState(); };
    panicButton.onClick = [this] { if (panicCallback) panicCallback(); };

    std::array<juce::Component*, 8> components { &oscBank, &filterBank, &ampBank, &filterEnvBank, &lfoBank, &effectsBank, &demoButton, &panicButton };
    for (auto* component : components)
        addAndMakeVisible(component);
}

SynthUI::~SynthUI()
{
    setLookAndFeel(nullptr);
}

void SynthUI::setPanicCallback(std::function<void()> callback)
{
    panicCallback = std::move(callback);
}

void SynthUI::resized()
{
    auto area = getLocalBounds().reduced(12);
    auto top = area.removeFromTop(230);
    oscBank.setBounds(top.removeFromLeft(area.getWidth() * 2 / 3).reduced(4));
    filterBank.setBounds(top.reduced(4));
    auto middle = area.removeFromTop(190);
    ampBank.setBounds(middle.removeFromLeft(area.getWidth() / 3).reduced(4));
    filterEnvBank.setBounds(middle.removeFromLeft(area.getWidth() / 3).reduced(4));
    lfoBank.setBounds(middle.reduced(4));
    auto bottom = area.removeFromTop(190);
    effectsBank.setBounds(bottom.removeFromLeft(area.getWidth() * 3 / 4).reduced(4));
    auto buttons = bottom.reduced(10);
    demoButton.setBounds(buttons.removeFromTop(42));
    buttons.removeFromTop(12);
    panicButton.setBounds(buttons.removeFromTop(42));
}

void SynthUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff070912));
    auto header = getLocalBounds().removeFromTop(56);
    g.setColour(juce::Colour(0xff151c31));
    g.fillRect(header);
    g.setColour(juce::Colour(0xffffd76b));
    g.setFont(juce::Font(25.0f, juce::Font::bold));
    g.drawText("DIGITAL WORKSTATION SYNTH", header.reduced(18, 0), juce::Justification::centredLeft);
    g.setColour(juce::Colour(0xff8ba9d8));
    g.setFont(juce::Font(13.0f));
    g.drawText("Original 90s-style partial synth with factory-style demo riffs", header.reduced(18, 0), juce::Justification::centredRight);
}