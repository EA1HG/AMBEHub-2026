#include "protocol/AMBE3000Protocol.h"
#include "protocol/DV3KCommands.h"

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
    AMBEFrame frame;

    frame.command = DV3KCommands::RESET_SOFTCFG;

    frame.payload =
    {
        0x05,
        0x00,
        0x00,
        0x0F,
        0x00,
        0x00
    };

    frame.length =
        static_cast<uint16_t>(
            frame.payload.size() + 1);

    return frame.serialize();
}

std::vector<uint8_t>
AMBE3000Protocol::buildProductId()
{
    AMBEFrame frame;

    frame.length = 1;
    frame.command = DV3KCommands::PRODUCT_ID;

    return frame.serialize();
}

std::vector<uint8_t>
AMBE3000Protocol::buildVersion()
{
    AMBEFrame frame;

    frame.length = 1;
    frame.command = DV3KCommands::VERSION;

    return frame.serialize();
}

std::vector<uint8_t>
AMBE3000Protocol::buildSetDMR()
{
    return
    {
        0x61,
        0x00,
        0x0D,
        0x00,
        0x0A,
        0x04,
        0x31,
        0x07,
        0x54,
        0x24,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x6F,
        0x48
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

 AMBEFrame
AMBE3000Protocol::buildEncodeSpeech(
    const PCMFrame& pcm)
{
    AMBEFrame frame;

    //
    // Comando PCM
    //

    frame.command = DV3KCommands::PCM;

    //
    // Packet Type = Speech
    //

    frame.appendByte(0x02);

    //
    // Vocoder Channel = 0
    //

    frame.appendByte(0x40);
    frame.appendByte(0x00);

    //
    // Speech Length = 160 samples (0x00A0)
    //

    frame.appendByte(0x00);
    frame.appendByte(0xA0);

    //
    // PCM
    //

    frame.appendData(
        pcm.toBytes());

    return frame;
}

AMBEFrame
AMBE3000Protocol::buildDecodeSpeech(
    const AMBEVoiceFrame&)
{
    AMBEFrame frame;

    //
    // TODO:
    // Construir el paquete AMBE -> PCM
    //

    return frame;
}