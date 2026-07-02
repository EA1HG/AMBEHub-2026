#ifndef DV3KAUDIOPROTOCOL_H
#define DV3KAUDIOPROTOCOL_H

#include <vector>
#include <cstdint>

#include "protocol/PCMFrame.h"
#include "protocol/AMBEVoiceFrame.h"

class DV3KAudioProtocol
{
public:

    // PCM -> DV3000
    static std::vector<uint8_t> buildEncodePCM(
        const PCMFrame& pcm);

    // AMBE -> DV3000
    static std::vector<uint8_t> buildDecodeAMBE(
        const AMBEVoiceFrame& ambe);

};

#endif