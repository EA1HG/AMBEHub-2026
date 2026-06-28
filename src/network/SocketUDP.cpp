#include "network/SocketUDP.h"

#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

SocketUDP::SocketUDP()
{
    m_socket = -1;
}

SocketUDP::~SocketUDP()
{
    close();
}

bool SocketUDP::open(int port)
{
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if (m_socket < 0)
        return false;

    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(
            m_socket,
            (sockaddr*)&addr,
            sizeof(addr)) < 0)
    {
        return false;
    }

    return true;
}

bool SocketUDP::sendPacket(
    const UDPEndpoint& endpoint,
    const Packet& packet)
{
    auto buffer = packet.encode();

    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(endpoint.port);

    inet_aton(
        endpoint.host.c_str(),
        &addr.sin_addr);

    int sent = sendto(
        m_socket,
        buffer.data(),
        buffer.size(),
        0,
        (sockaddr*)&addr,
        sizeof(addr));

    return sent == (int)buffer.size();
}

bool SocketUDP::receivePacket(
    Packet& packet,
    UDPEndpoint& endpoint)
{
    uint8_t buffer[2048];

    sockaddr_in client{};

    socklen_t len = sizeof(client);

    int bytes = recvfrom(
        m_socket,
        buffer,
        sizeof(buffer),
        0,
        (sockaddr*)&client,
        &len);

    if (bytes <= 0)
        return false;

    endpoint.host = inet_ntoa(client.sin_addr);
    endpoint.port = ntohs(client.sin_port);

    return Packet::decode(
        buffer,
        bytes,
        packet);
}

void SocketUDP::close()
{
    if (m_socket >= 0)
    {
        ::close(m_socket);

        m_socket = -1;
    }
}