#ifndef PCMGENERATOR_H
#define PCMGENERATOR_H

#include "protocol/PCMFrame.h"

class PCMGenerator
{
public:

    static void generateSilence(
        PCMFrame& frame);

    static void generateTone(
        PCMFrame& frame,
        double frequency,
        int sampleRate = 8000,
        int amplitude = 12000);
};

#endif