#ifndef SOCKETUDP_H
#define SOCKETUDP_H

#include <string>
#include <cstdint>

#include "protocol/Packet.h"

struct UDPEndpoint
{
    std::string host;
    int port;
};

class SocketUDP
{
public:

    SocketUDP();

    ~SocketUDP();

    bool open(int port);

    bool sendPacket(
        const UDPEndpoint& endpoint,
        const Packet& packet);

    bool receivePacket(
        Packet& packet,
        UDPEndpoint& endpoint);

    void close();

private:

    int m_socket;
};

#endif