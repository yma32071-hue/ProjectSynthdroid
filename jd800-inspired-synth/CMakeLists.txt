cmake_minimum_required(VERSION 3.22)

project(DigitalWorkstationSynth VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.7
)
FetchContent_MakeAvailable(JUCE)

set(SYNTH_SOURCES
    Source/Synth/SynthParameters.h
    Source/Synth/Sound.h
    Source/Synth/Sound.cpp
    Source/Synth/Oscillator.h
    Source/Synth/Oscillator.cpp
    Source/Synth/Envelope.h
    Source/Synth/Envelope.cpp
    Source/Synth/LFO.h
    Source/Synth/LFO.cpp
    Source/Synth/Filter.h
    Source/Synth/Filter.cpp
    Source/Synth/Voice.h
    Source/Synth/Voice.cpp
    Source/Synth/SynthEngine.h
    Source/Synth/SynthEngine.cpp
    Source/FX/Chorus.h
    Source/FX/Chorus.cpp
    Source/FX/Delay.h
    Source/FX/Delay.cpp
    Source/FX/Reverb.h
    Source/FX/Reverb.cpp
)

set(UI_SOURCES
    Source/UI/LookAndFeel.h
    Source/UI/LookAndFeel.cpp
    Source/UI/SliderBank.h
    Source/UI/SliderBank.cpp
    Source/UI/SynthUI.h
    Source/UI/SynthUI.cpp
)

juce_add_gui_app(DigitalWorkstationSynth
    PRODUCT_NAME "Digital Workstation Synth"
    COMPANY_NAME "Original Digital Instruments"
    BUNDLE_ID "com.originaldigitalinstruments.digitalworkstationsynth"
)

target_sources(DigitalWorkstationSynth PRIVATE
    Source/Main.cpp
    Source/MainComponent.h
    Source/MainComponent.cpp
    ${SYNTH_SOURCES}
    ${UI_SOURCES}
)

juce_generate_juce_header(DigitalWorkstationSynth)

target_compile_definitions(DigitalWorkstationSynth PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(DigitalWorkstationSynth PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

set(PLUGIN_FORMATS Standalone VST3)
if(APPLE)
    list(APPEND PLUGIN_FORMATS AU)
endif()

juce_add_plugin(DigitalWorkstationSynthPlugin
    COMPANY_NAME "Original Digital Instruments"
    PRODUCT_NAME "Digital Workstation Synth"
    BUNDLE_ID "com.originaldigitalinstruments.digitalworkstationsynthplugin"
    PLUGIN_MANUFACTURER_CODE Odis
    PLUGIN_CODE Dws1
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    FORMATS ${PLUGIN_FORMATS}
)

target_sources(DigitalWorkstationSynthPlugin PRIVATE
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    ${SYNTH_SOURCES}
)

juce_generate_juce_header(DigitalWorkstationSynthPlugin)

target_compile_definitions(DigitalWorkstationSynthPlugin PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(DigitalWorkstationSynthPlugin PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)