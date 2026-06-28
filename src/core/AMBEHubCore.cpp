#include "core/AMBEHubCore.h"

#include "Logger.h"

AMBEHubCore::AMBEHubCore()
{
}

bool AMBEHubCore::processPacket(
    const Packet& packet,
    const UDPEndpoint& endpoint,
    Packet& response)
{
    Session* session =
        m_sessions.find(endpoint.host, endpoint.port);

    if (session == nullptr)
    {
        session = &m_sessions.create(
            endpoint.host,
            endpoint.port);

        Logger::info(
            "Nueva sesión creada: "
            + endpoint.host
            + ":"
            + std::to_string(endpoint.port));
    }

    session->lastPing =
        std::chrono::steady_clock::now();

    DispatchResult result =
        m_dispatcher.dispatch(packet);

    switch(result.type)
    {
        case PacketType::HELLO:
        {
            HelloMessage hello;

            if(packet.getPayload(hello))
            {
                session->clientName = hello.clientName;
                session->clientVersion = hello.clientVersion;

                Logger::info(
                    "Cliente registrado: "
                    + session->clientName
                    + " "
                    + session->clientVersion);
            }

            break;
        }

        case PacketType::LOGIN:
        {
            LoginMessage login;

            if(packet.getPayload(login))
            {
                session->username = login.callsign;
                session->authenticated = true;
                session->state = SessionState::AUTHENTICATED;

                Logger::info(
                    "Usuario autenticado: "
                    + session->username);
            }

            break;
        }

        case PacketType::PING:
        {
            session->lastPing =
                std::chrono::steady_clock::now();

            break;
        }

        default:
            break;
    }

    if(!result.hasResponse)
        return false;

    response = result.response;

    return true;
}