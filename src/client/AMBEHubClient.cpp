#include "client/AMBEHubClient.h"

#include "Logger.h"
#include "protocol/Messages.h"
#include "protocol/Packet.h"

#include <cstring>

AMBEHubClient::AMBEHubClient()
{
}

bool AMBEHubClient::connect(
    const std::string& host,
    int port)
{
    m_server.host = host;
    m_server.port = port;

    if (!m_socket.open(0))
    {
        Logger::error("No se pudo abrir el socket.");
        return false;
    }

    Logger::info(
        "Conectado a "
        + host
        + ":"
        + std::to_string(port));

    return true;
}

bool AMBEHubClient::hello()
{
    Logger::info("Enviando HELLO...");

    HelloMessage hello{};

    hello.protocolVersion = 1;

    std::strncpy(
        hello.clientName,
        "AMBEHubClient",
        sizeof(hello.clientName) - 1);

    std::strncpy(
        hello.clientVersion,
        "0.10",
        sizeof(hello.clientVersion) - 1);

    Packet packet;

    packet.header.type =
        static_cast<uint16_t>(PacketType::HELLO);

    packet.setPayload(hello);

    if (!m_socket.sendPacket(m_server, packet))
    {
        Logger::error("No se pudo enviar HELLO.");
        return false;
    }

    Packet response;

    UDPEndpoint endpoint;

    Logger::info("Esperando HELLO_ACK...");

    if (!m_socket.receivePacket(response, endpoint))
    {
        Logger::error("No se recibió HELLO_ACK.");
        return false;
    }

    if (static_cast<PacketType>(response.header.type)
            != PacketType::HELLO_ACK)
    {
        Logger::warning("Respuesta inesperada.");
        return false;
    }

    Logger::info("HELLO_ACK recibido.");

    return true;
}

bool AMBEHubClient::ping()
{
    Logger::info("Enviando PING...");

    Packet packet;

    packet.header.type =
        static_cast<uint16_t>(PacketType::PING);

    packet.header.length = 0;

    if (!m_socket.sendPacket(m_server, packet))
    {
        Logger::error("No se pudo enviar el PING.");
        return false;
    }

    Packet response;

    UDPEndpoint endpoint;

    Logger::info("Esperando PONG...");

    if (!m_socket.receivePacket(response, endpoint))
    {
        Logger::error("No se recibió PONG.");
        return false;
    }

    if (static_cast<PacketType>(response.header.type)
            != PacketType::PONG)
    {
        Logger::warning("Respuesta inesperada.");
        return false;
    }

    Logger::info("PONG recibido correctamente.");

    return true;
}