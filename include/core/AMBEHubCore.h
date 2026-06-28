#ifndef AMBEHUBCORE_H
#define AMBEHUBCORE_H

#include "network/SocketUDP.h"
#include "protocol/Messages.h"
#include "protocol/Packet.h"
#include "protocol/PacketDispatcher.h"
#include "session/SessionManager.h"

class AMBEHubCore
{
public:

    AMBEHubCore();

    bool processPacket(
        const Packet& packet,
        const UDPEndpoint& endpoint,
        Packet& response);

private:

    SessionManager m_sessions;

    PacketDispatcher m_dispatcher;
};

#endif