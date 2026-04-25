cmake_minimum_required(VERSION 3.22)

project(ProjectSynthdroid VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================
# 🔥 JUCE SETUP
# ============================================

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 7.0.9
)

FetchContent_MakeAvailable(JUCE)

# ============================================
# 🎹 APP TARGET (ANDROID ENABLED)
# ============================================

juce_add_gui_app(ProjectSynthdroid
    PRODUCT_NAME "Project Synthdroid"
    BUNDLE_ID com.projectsynthdroid.yui
    VERSION 1.0.0
)

# REQUIRED FOR ANDROID APK GENERATION
set_target_properties(ProjectSynthdroid PROPERTIES
    JUCE_ANDROID_PACKAGE_NAME "com.projectsynthdroid.yui"
)

# ============================================
# 📁 SOURCE FILES
# ============================================

target_sources(ProjectSynthdroid PRIVATE

    # Core
    Source/Main.cpp
    Source/MainComponent.cpp

    # UI
    Source/UI/MainView.cpp
    Source/UI/PianoKeyboard.cpp
    Source/UI/KeyComponent.cpp
    Source/UI/LookAndFeel.cpp
    Source/UI/SynthUI.cpp
    Source/UI/SliderBank.cpp

    # Synth Engine
    Source/Synth/SynthEngine.cpp
    Source/Synth/Voice.cpp
    Source/Synth/Sound.cpp
    Source/Synth/Oscillator.cpp
    Source/Synth/Envelope.cpp
    Source/Synth/Filter.cpp
    Source/Synth/LFO.cpp

    # FX
    Source/FX/Chorus.cpp
    Source/FX/Delay.cpp
    Source/FX/Reverb.cpp

    # Piano Engine
    Source/Piano/PianoSampler.cpp
    Source/Piano/PianoVoice.cpp
    Source/Piano/PianoSound.cpp
    Source/Audio/PianoAcousticEngine.cpp

    
)

# ============================================
# 🔊 JUCE MODULES
# ============================================

target_link_libraries(ProjectSynthdroid
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_dsp
        juce::juce_gui_extra
)

# ============================================
# ⚙️ DEFINITIONS
# ============================================

target_compile_definitions(ProjectSynthdroid
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_ANDROID=1
        JUCE_STANDALONE_APPLICATION=1
)

# ============================================
# 📦 ASSETS (YOUR PIANO SAMPLES)
# ============================================

# This makes JUCE include files in APK
file(GLOB_RECURSE SAMPLE_FILES
    "${CMAKE_SOURCE_DIR}/Source/Assets/Samples/Piano/*"
)

target_sources(ProjectSynthdroid PRIVATE ${SAMPLE_FILES})

source_group("Samples" FILES ${SAMPLE_FILES})

# ============================================
# 📱 ANDROID SETTINGS
# ============================================

if(ANDROID)
    target_compile_definitions(ProjectSynthdroid PRIVATE
        JUCE_ANDROID_API_VERSION=29
    )
endif()