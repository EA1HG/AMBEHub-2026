#ifndef AMBE3000PROTOCOL_H
#define AMBE3000PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "protocol/AMBEFrame.h"
#include "protocol/PCMFrame.h"
#include "protocol/AMBEVoiceFrame.h"

class AMBE3000Protocol
{
public:

    static std::vector<uint8_t> buildZeroPacket();

    static std::vector<uint8_t> buildResetSoftCfg();

    static std::vector<uint8_t> buildProductId();

    static std::vector<uint8_t> buildVersion();
    
    static std::vector<uint8_t> buildSetDMR();

    static bool isReady(
        const AMBEFrame& frame);

    static bool isProductId(
        const AMBEFrame& frame);

    static bool isVersion(
        const AMBEFrame& frame);

    //
    // Voz
    //

    static AMBEFrame buildEncodeSpeech(
        const PCMFrame& pcm);

    static AMBEFrame buildDecodeSpeech(
        const AMBEVoiceFrame& ambe);

    static std::string commandToString(
        uint16_t command);
};

#endif