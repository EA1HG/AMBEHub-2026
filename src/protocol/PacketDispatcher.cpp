#include "protocol/PacketDispatcher.h"

#include "Logger.h"
#include "protocol/Messages.h"

PacketDispatcher::PacketDispatcher()
{
}

DispatchResult PacketDispatcher::dispatch(
    const Packet& packet)
{
    DispatchResult result;

    result.hasResponse = false;

    PacketType type =
        static_cast<PacketType>(packet.header.type);

    result.type = type;

    switch(type)
    {
        case PacketType::HELLO:
        {
            Logger::info("HELLO recibido.");

            HelloMessage hello;

            if(packet.getPayload(hello))
            {
                Logger::info(
                    std::string("Cliente: ")
                    + hello.clientName
                    + " "
                    + hello.clientVersion);
            }

            result.hasResponse = true;

            result.response.header.type =
                static_cast<uint16_t>(PacketType::HELLO_ACK);

            result.response.header.length = 0;

            break;
        }

        case PacketType::LOGIN:
        {
            Logger::info("LOGIN recibido.");

            LoginMessage login;

            if(packet.getPayload(login))
            {
                Logger::info(
                    std::string("Callsign: ")
                    + login.callsign);
            }
            else
            {
                Logger::warning("LOGIN inválido.");
            }

            result.hasResponse = true;

            result.response.header.type =
                static_cast<uint16_t>(PacketType::LOGIN_OK);

            result.response.header.length = 0;

            break;
        }

        case PacketType::PING:
        {
            Logger::info("PING recibido.");

            result.hasResponse = true;

            result.response.header.type =
                static_cast<uint16_t>(PacketType::PONG);

            result.response.header.length = 0;

            break;
        }

        case PacketType::PONG:
        {
            Logger::info("PONG recibido.");
            break;
        }

        default:
        {
            Logger::warning("Paquete desconocido.");
            break;
        }
    }

    return result;
}