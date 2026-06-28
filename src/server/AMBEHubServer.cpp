#include "server/AMBEHubServer.h"

#include "Logger.h"

AMBEHubServer::AMBEHubServer()
{
}

bool AMBEHubServer::initialize()
{
    Logger::info("====================================");
    Logger::info("        AMBEHub Server 0.11");
    Logger::info("====================================");

    Logger::info("Inicializando DeviceManager...");

    if (!m_deviceManager.initialize())
    {
        Logger::error("No se pudo inicializar DeviceManager.");
        return false;
    }

    Logger::info("Inicializando servidor UDP...");

    if (!m_udp.start(62031))
    {
        Logger::error("No se pudo iniciar el servidor UDP.");
        return false;
    }

    Logger::info(
        "Dispositivos disponibles: "
        + std::to_string(m_deviceManager.count()));

    return true;
}

void AMBEHubServer::run()
{
    Logger::info("Servidor listo.");

    m_udp.run();

    m_deviceManager.shutdown();
}