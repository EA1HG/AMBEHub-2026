#ifndef AMBEHUBSERVER_H
#define AMBEHUBSERVER_H

#include "device/DeviceManager.h"
#include "network/UDPServer.h"

class AMBEHubServer
{
public:

    AMBEHubServer();

    bool initialize();

    void run();

private:

    UDPServer m_udp;

    DeviceManager m_deviceManager;
};

#endif