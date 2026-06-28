#include "network/UDPServer.h"

#include "Logger.h"

UDPServer::UDPServer()
{
}

bool UDPServer::start(int port)
{
    if (!m_socket.open(port))
    {
        Logger::error("No se pudo abrir el puerto UDP.");
        return false;
    }

    Logger::info(
        "UDP escuchando en el puerto "
        + std::to_string(port));

    return true;
}

void UDPServer::run()
{
    while (true)
    {
        receivePacket();
    }
}

bool UDPServer::receivePacket()
{
    Packet packet;

    UDPEndpoint endpoint;

    if (!m_socket.receivePacket(packet, endpoint))
        return false;

    Packet response;

    if (m_core.processPacket(
            packet,
            endpoint,
            response))
    {
        if (!m_socket.sendPacket(endpoint, response))
        {
            Logger::error(
                "No se pudo enviar la respuesta.");
        }
    }

    return true;
}