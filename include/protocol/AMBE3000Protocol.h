#ifndef AMBE3000PROTOCOL_H
#define AMBE3000PROTOCOL_H

#include <cstdint>
#include <vector>

class AMBE3000Protocol
{
public:

    static std::vector<uint8_t> buildZeroPacket();

    static std::vector<uint8_t> buildResetSoftCfg();

    static std::vector<uint8_t> buildProductId();

    static std::vector<uint8_t> buildVersion();

    static bool isReady(
        const std::vector<uint8_t>& frame);
};

#endif