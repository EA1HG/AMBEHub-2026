#include "Logger.h"
#include "server/AMBEHubServer.h"

int main()
{
    Logger::info("AMBEHub iniciado");

    AMBEHubServer server;

    if (!server.initialize())
    {
        Logger::error("No se pudo inicializar el servidor.");
        return 1;
    }

    server.run();

    return 0;
}