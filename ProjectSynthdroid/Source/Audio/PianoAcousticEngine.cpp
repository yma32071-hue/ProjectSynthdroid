#include "PianoAcousticEngine.h"
#include "BinaryData.h"

int PianoAcousticEngine::getLayer(float v)
{
    if (v < 0.3f) return 0;
    if (v < 0.6f) return 1;
    if (v < 0.85f) return 2;
    return 3;
}
void PianoAcousticEngine::init()
{
    loadFromBinaryData();
}