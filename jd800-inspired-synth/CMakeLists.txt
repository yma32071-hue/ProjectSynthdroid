cmake_minimum_required(VERSION 3.22)

project(ProjectSynthdroid VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# =========================================
# JUCE
# =========================================
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.7
)

FetchContent_MakeAvailable(JUCE)

# =========================================
# ANDROID SAFE SETTINGS
# =========================================
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)

# =========================================
# CORE PIANO ENGINE (lightweight)
# =========================================
set(ENGINE
    Source/Piano/PianoSound.cpp
    Source/Piano/PianoVoice.cpp
    Source/Piano/PianoSampler.cpp
)

# =========================================
# MOBILE UI (ORG STYLE)
# =========================================
set(UI
    Source/UI/MainView.cpp
    Source/UI/PianoKeyboard.cpp
    Source/UI/LookAndFeel.cpp
)

# =========================================
# ANDROID + DESKTOP STANDALONE APP
# =========================================
juce_add_gui_app(ProjectSynthdroid
    PRODUCT_NAME "Synthdroid Piano"
    COMPANY_NAME "Synthdroid Audio"
    BUNDLE_ID "com.synthdroid.piano"
)

target_sources(ProjectSynthdroid PRIVATE
    Source/Main.cpp
    Source/MainComponent.cpp

    ${ENGINE}
    ${UI}
)

target_compile_definitions(ProjectSynthdroid PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0

    # Android audio stability tweaks
    JUCE_ALSA=1
)

# =========================================
# JUCE MODULES (ANDROID COMPATIBLE)
# =========================================
target_link_libraries(ProjectSynthdroid PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_utils
    juce::juce_gui_basics
    juce::juce_gui_extra
)
