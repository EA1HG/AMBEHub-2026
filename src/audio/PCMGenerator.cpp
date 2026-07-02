#include "audio/PCMGenerator.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void PCMGenerator::generateSilence(
    PCMFrame& frame)
{
    frame.clear();
}

void PCMGenerator::generateTone(
    PCMFrame& frame,
    double frequency,
    int sampleRate,
    int amplitude)
{
    double phase = 0.0;

    double step =
        (2.0 * M_PI * frequency) /
        sampleRate;

    for (std::size_t i = 0;
         i < PCMFrame::SAMPLE_COUNT;
         i++)
    {
        frame[i] =
            static_cast<int16_t>(
                amplitude *
                std::sin(phase));

        phase += step;
    }
}