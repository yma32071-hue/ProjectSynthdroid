#include "PianoVoice.h"
#include <iostream>

void PianoVoice::noteOn(int note, float velocity)
{
    std::cout << "Note ON: " << note << std::endl;
}

void PianoVoice::noteOff()
{
    std::cout << "Note OFF" << std::endl;
}