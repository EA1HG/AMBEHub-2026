#ifndef CODECENGINE_H
#define CODECENGINE_H

#include "device/IDevice.h"
#include "protocol/PCMFrame.h"
#include "protocol/AMBEVoiceFrame.h"

class CodecEngine
{
public:

    CodecEngine();

    //
    // PCM -> AMBE
    //
    bool encode(
        IDevice& device,
        const PCMFrame& pcm,
        AMBEVoiceFrame& ambe);

    //
    // AMBE -> PCM
    //
    bool decode(
        IDevice& device,
        const AMBEVoiceFrame& ambe,
        PCMFrame& pcm);
};

#endif