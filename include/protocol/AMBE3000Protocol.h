#ifndef AMBE3000PROTOCOL_H
#define AMBE3000PROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "protocol/AMBEFrame.h"

class AMBE3000Protocol
{
public:

    static std::vector<uint8_t> buildZeroPacket();

    static std::vector<uint8_t> buildResetSoftCfg();

    static std::vector<uint8_t> buildProductId();

    static std::vector<uint8_t> buildVersion();

    static bool isReady(
        const AMBEFrame& frame);

    static bool isProductId(
        const AMBEFrame& frame);

    static bool isVersion(
        const AMBEFrame& frame);

    //
    // NUEVO
    //

    static std::string commandToString(
        uint16_t command);
};

#endif