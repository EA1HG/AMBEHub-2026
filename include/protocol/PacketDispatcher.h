#ifndef PACKETDISPATCHER_H
#define PACKETDISPATCHER_H

#include "protocol/Packet.h"

struct DispatchResult
{
    bool hasResponse;

    PacketType type;

    Packet response;

    DispatchResult()
    {
        hasResponse = false;
        type = PacketType::UNKNOWN;
    }
};

class PacketDispatcher
{
public:

    PacketDispatcher();

    DispatchResult dispatch(
        const Packet& packet);
};

#endif