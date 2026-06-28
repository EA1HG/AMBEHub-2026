#ifndef PACKET_H
#define PACKET_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

constexpr uint32_t AMBEHUB_MAGIC = 0x41485542; // "AHUB"

enum class PacketType : uint16_t
{
    UNKNOWN = 0,

    HELLO      = 1,
    HELLO_ACK  = 2,

    LOGIN       = 10,
    LOGIN_OK    = 11,
    LOGIN_FAIL  = 12,

    PING = 20,
    PONG = 21,

    AUDIO = 50
};

#pragma pack(push,1)

struct PacketHeader
{
    uint32_t magic;
    uint16_t version;
    uint16_t type;
    uint32_t length;
};

#pragma pack(pop)

class Packet
{
public:

    Packet();

    PacketHeader header;

    std::vector<uint8_t> payload;

    std::vector<uint8_t> encode() const;

    static bool decode(
        const uint8_t* data,
        std::size_t size,
        Packet& packet);

    template<typename T>
    void setPayload(const T& data)
    {
        payload.resize(sizeof(T));

        std::memcpy(
            payload.data(),
            &data,
            sizeof(T));

        header.length = sizeof(T);
    }

    template<typename T>
    bool getPayload(T& data) const
    {
        if (payload.size() != sizeof(T))
            return false;

        std::memcpy(
            &data,
            payload.data(),
            sizeof(T));

        return true;
    }
};

#endif