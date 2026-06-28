#ifndef AMBEHUBCLIENT_H
#define AMBEHUBCLIENT_H

#include <string>

#include "network/SocketUDP.h"

class AMBEHubClient
{
public:

    AMBEHubClient();

    bool connect(
        const std::string& host,
        int port);

    bool hello();

    bool login(
        const std::string& callsign,
        const std::string& password);

    bool ping();

private:

    SocketUDP m_socket;

    UDPEndpoint m_server;
};

#endif