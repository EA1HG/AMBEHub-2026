#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "network/SocketUDP.h"
#include "core/AMBEHubCore.h"

class UDPServer
{
public:

    UDPServer();

    bool start(int port);

    void run();

private:

    bool receivePacket();

    SocketUDP m_socket;

    AMBEHubCore m_core;
};

#endif