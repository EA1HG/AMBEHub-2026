#ifndef AMBE3000PROTOCOL_H
#define AMBE3000PROTOCOL_H

#include <cstdint>
#include <vector>

#include "protocol/AMBEFrame.h"

class AMBE3000Protocol
{
public:

    static std::vector<uint8_t> buildZeroPacket();

    static std::vector<uint8_t> buildResetSoftCfg();

    static std::vector<uint8_t> buildProductId();

    static std::vector<uint8_t> buildVersion();

    /*
     * Comprobaciones de respuestas del codec.
     */

    static bool isReady(
        const AMBEFrame& frame);

    static bool isProductId(
        const AMBEFrame& frame);

    static bool isVersion(
        const AMBEFrame& frame);
};

#endif