#include "codec/CodecEngine.h"
#include <vector>
#include "protocol/DV3KAudioProtocol.h"
#include <iostream>
#include <iomanip>

CodecEngine::CodecEngine()
{
}

bool CodecEngine::encode(
    IDevice& device,
    const PCMFrame& pcm,
    AMBEVoiceFrame& ambe)
{
    std::vector<uint8_t> tx =
    DV3KAudioProtocol::buildEncodePCM(pcm);

std::vector<uint8_t> rx;

if (!device.exchangeRaw(tx, rx))
    return false;
    
    std::cout << "\nRX (" << rx.size() << " bytes): ";

for (uint8_t b : rx)
{
    std::cout
        << std::uppercase
        << std::hex
        << std::setw(2)
        << std::setfill('0')
        << static_cast<int>(b)
        << ' ';
}

std::cout << std::dec << std::endl;

// Debe devolver:
// 61 00 0B 01 01 48 + 9 bytes

if (rx.size() != 15)
    return false;

if (rx[0] != 0x61)
    return false;

if (rx[3] != 0x01)
    return false;

if (rx[4] != 0x01)
    return false;

if (rx[5] != 0x48)
    return false;

std::vector<uint8_t> voice(
    rx.begin() + 6,
    rx.end());

return ambe.fromBytes(voice);
}

bool CodecEngine::decode(
    IDevice&,
    const AMBEVoiceFrame&,
    PCMFrame&)
{
    //
    // Próximamente:
    // AMBE -> DV3K -> PCM
    //
    return false;
}