#ifndef PACKETSERIALIZER_H
#define PACKETSERIALIZER_H

#include <vector>

#include "protocol/Packet.h"

class PacketSerializer
{
public:

    static std::vector<uint8_t> encode(
        const Packet& packet);

    static bool decode(
        const uint8_t* data,
        std::size_t size,
        Packet& packet);
};

#endif