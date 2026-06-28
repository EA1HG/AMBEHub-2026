#include "protocol/Packet.h"

#include <cstring>

Packet::Packet()
{
    header.magic = AMBEHUB_MAGIC;
    header.version = 1;
    header.type = static_cast<uint16_t>(PacketType::UNKNOWN);
    header.length = 0;
}

std::vector<uint8_t> Packet::encode() const
{
    std::vector<uint8_t> buffer;

    buffer.resize(sizeof(PacketHeader) + payload.size());

    std::memcpy(buffer.data(), &header, sizeof(PacketHeader));

    if (!payload.empty())
    {
        std::memcpy(
            buffer.data() + sizeof(PacketHeader),
            payload.data(),
            payload.size());
    }

    return buffer;
}

bool Packet::decode(
    const uint8_t* data,
    std::size_t size,
    Packet& packet)
{
    if (size < sizeof(PacketHeader))
        return false;

    std::memcpy(
        &packet.header,
        data,
        sizeof(PacketHeader));

    if (packet.header.magic != AMBEHUB_MAGIC)
        return false;

    if (size < sizeof(PacketHeader) + packet.header.length)
        return false;

    packet.payload.resize(packet.header.length);

    if (packet.header.length > 0)
    {
        std::memcpy(
            packet.payload.data(),
            data + sizeof(PacketHeader),
            packet.header.length);
    }

    return true;
}