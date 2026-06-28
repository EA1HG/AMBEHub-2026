#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "device/SerialPort.h"
#include "protocol/AMBE3000Protocol.h"
#include "protocol/AMBEFrame.h"

static void dumpHex(const std::vector<uint8_t>& data)
{
    if (data.empty())
    {
        std::cout << "\n  <sin datos>\n";
        return;
    }

    for (std::size_t i = 0; i < data.size(); ++i)
    {
        if ((i % 16) == 0)
            std::cout << "\n  ";

        std::cout
            << std::uppercase
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(data[i])
            << ' ';
    }

    std::cout << std::dec << "\n";
}

static void executeCommand(
    SerialPort& serial,
    const std::vector<uint8_t>& tx,
    const std::string& name)
{
    std::cout << "\n=========================================\n";
    std::cout << name << "\n";
    std::cout << "=========================================\n";

    std::cout << "\nTX (" << tx.size() << " bytes)";
    dumpHex(tx);

    if (!serial.write(tx))
    {
        std::cout << "\nERROR enviando comando.\n";
        return;
    }

    std::vector<uint8_t> rx;

    if (!serial.readFrame(rx, 2000, 20))
    {
        std::cout << "\nTimeout esperando respuesta.\n";
        return;
    }

    std::cout << "\nRX (" << rx.size() << " bytes)";
    dumpHex(rx);

    AMBEFrame frame;

    if (!frame.deserialize(rx))
    {
        std::cout << "\nNo se pudo interpretar la trama.\n";
        return;
    }

    std::cout << "\n" << frame.toString();

    std::cout << "Tipo : "
              << AMBE3000Protocol::commandToString(frame.command)
              << "\n";
}

int main()
{
    SerialPort serial;

    std::cout
        << "\n=========================================\n"
        << "      AMBEHub Diagnostic 0.4\n"
        << "=========================================\n";

    if (!serial.open(
            "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0",
            230400))
    {
        std::cout << "\nNo se pudo abrir el puerto serie.\n";
        return 1;
    }

    std::cout << "\nPuerto abierto correctamente.\n";

    for (;;)
    {
        std::cout
            << "\n"
            << "1) RESET_SOFTCFG\n"
            << "2) PRODUCT_ID\n"
            << "3) VERSION\n"
            << "0) Salir\n"
            << "\nOpcion: ";

        int option;

        std::cin >> option;

        switch (option)
        {
            case 1:
                executeCommand(
                    serial,
                    AMBE3000Protocol::buildResetSoftCfg(),
                    "RESET_SOFTCFG");
                break;

            case 2:
                executeCommand(
                    serial,
                    AMBE3000Protocol::buildProductId(),
                    "PRODUCT_ID");
                break;

            case 3:
                executeCommand(
                    serial,
                    AMBE3000Protocol::buildVersion(),
                    "VERSION");
                break;

            case 0:
                return 0;

            default:
                std::cout << "\nOpción no válida.\n";
                break;
        }
    }
}