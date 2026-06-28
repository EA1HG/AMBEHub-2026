#include "protocol/PacketSerializer.h"

std::vector<uint8_t> PacketSerializer::encode(
    const Packet& packet)
{
    return packet.encode();
}

bool PacketSerializer::decode(
    const uint8_t* data,
    std::size_t size,
    Packet& packet)
{
    return Packet::decode(
        data,
        size,
        packet);
}