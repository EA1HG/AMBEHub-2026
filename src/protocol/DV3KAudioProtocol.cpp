#include "protocol/DV3KAudioProtocol.h"

std::vector<uint8_t>
DV3KAudioProtocol::buildEncodePCM(
    const PCMFrame& pcm)
{
    std::vector<uint8_t> packet;

    // 4 bytes cabecera + 2 bytes payload + 320 bytes PCM
    packet.reserve(326);

    // Start byte
    packet.push_back(0x61);

    // Longitud del payload (322 = 0x0142)
    packet.push_back(0x01);
    packet.push_back(0x42);

    // Packet Type = AUDIO
    packet.push_back(0x02);

    // Canal
    packet.push_back(0x00);

    // 160 muestras PCM
    packet.push_back(0xA0);

    // PCM (320 bytes)
    std::vector<uint8_t> pcmBytes = pcm.toBytes();

    packet.insert(
        packet.end(),
        pcmBytes.begin(),
        pcmBytes.end());

    return packet;
}

std::vector<uint8_t>
DV3KAudioProtocol::buildDecodeAMBE(
    const AMBEVoiceFrame& ambe)
{
    std::vector<uint8_t> packet;

    // 4 bytes cabecera + 2 bytes payload + 9 bytes AMBE
    packet.reserve(15);

    packet.push_back(0x61);

    // Longitud = 11 (0x000B)
    packet.push_back(0x00);
    packet.push_back(0x0B);

    // Packet Type = AMBE
    packet.push_back(0x01);

    // Canal
    packet.push_back(0x01);

    // 72 bits
    packet.push_back(0x48);

    const auto& voice = ambe.data();

    packet.insert(
        packet.end(),
        voice.begin(),
        voice.end());

    return packet;
}