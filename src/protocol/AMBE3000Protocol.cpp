#include "protocol/AMBE3000Protocol.h"

std::vector<uint8_t>
AMBE3000Protocol::buildZeroPacket()
{
    return
    {
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };
}

std::vector<uint8_t>
AMBE3000Protocol::buildResetSoftCfg()
{
    return
    {
        0x61,
        0x00,
        0x07,
        0x00,
        0x34,
        0x05,
        0x00,
        0x00,
        0x0F,
        0x00,
        0x00
    };
}

std::vector<uint8_t>
AMBE3000Protocol::buildProductId()
{
    return
    {
        0x61,
        0x00,
        0x01,
        0x00,
        0x30
    };
}

std::vector<uint8_t>
AMBE3000Protocol::buildVersion()
{
    return
    {
        0x61,
        0x00,
        0x01,
        0x00,
        0x31
    };
}

bool
AMBE3000Protocol::isReady(
    const std::vector<uint8_t>& frame)
{
    if (frame.size() < 5)
        return false;

    return frame[0] == 0x61 &&
           frame[4] == 0x39;
}