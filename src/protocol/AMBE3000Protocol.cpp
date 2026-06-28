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
    const AMBEFrame& frame)
{
    return
        frame.start == 0x61 &&
        frame.command == 0x0039;
}

bool
AMBE3000Protocol::isProductId(
    const AMBEFrame& frame)
{
    return
        frame.start == 0x61 &&
        frame.command == 0x0030;
}

bool
AMBE3000Protocol::isVersion(
    const AMBEFrame& frame)
{
    return
        frame.start == 0x61 &&
        frame.command == 0x0031;
}

std::string
AMBE3000Protocol::commandToString(
    uint16_t command)
{
    switch (command)
    {
        case 0x0030:
            return "PRODUCT_ID";

        case 0x0031:
            return "VERSION";

        case 0x0034:
            return "RESET_SOFTCFG";

        case 0x0039:
            return "READY";

        case 0x0001:
            return "AMBE";

        case 0x0002:
            return "PCM";

        default:
            return "UNKNOWN";
    }
}