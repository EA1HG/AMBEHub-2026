#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include "device/SerialPort.h"
#include "protocol/AMBE3000Protocol.h"
#include "protocol/AMBEFrame.h"
#include "protocol/DV3KResponse.h"

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

    std::cout << std::dec << '\n';
}

static void showFrame(const std::vector<uint8_t>& rx)
{
    std::cout << "\nRX (" << rx.size() << " bytes)";
    dumpHex(rx);

    //
    // Respuestas RAW del DV3K
    //

    if (!rx.empty() && rx[0] == 0x00)
    {
        DV3KResponse response;

        if (response.parse(rx))
        {
            std::cout
                << "\nTIPO      : "
                << response.commandName()
                << "\n";

            if (response.isProductId())
            {
                std::cout
                    << "PRODUCTO  : "
                    << response.productId()
                    << "\n";
            }

            if (response.isVersion())
            {
                std::cout
                    << "FIRMWARE  : "
                    << response.version()
                    << "\n";
            }

            if (response.isReady())
            {
                std::cout
                    << "ESTADO    : READY\n";
            }

            return;
        }
    }

    //
    // Trama completa
    //

    AMBEFrame frame;

    if (!frame.deserialize(rx))
    {
        std::cout
            << "\nNo se pudo interpretar la trama.\n";

        return;
    }

    std::cout
        << '\n'
        << frame.toString();

    std::cout
        << "TIPO      : "
        << AMBE3000Protocol::commandToString(
               frame.command)
        << "\n";
}

static void sendCommand(
    SerialPort& serial,
    const std::string& title,
    const std::vector<uint8_t>& tx)
{
    std::cout << "\n=========================================\n";
    std::cout << title << '\n';
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

    showFrame(rx);
}

static std::vector<uint8_t> parseHexString(
    const std::string& text)
{
    std::vector<uint8_t> data;

    std::stringstream ss(text);

    std::string token;

    while (ss >> token)
    {
        unsigned int value = 0;

        std::stringstream hex;

        hex << std::hex << token;

        hex >> value;

        data.push_back(
            static_cast<uint8_t>(value));
    }

    return data;
}

int main()
{
    SerialPort serial;

    std::cout
        << "\n=========================================\n"
        << "      AMBEHub Diagnostic 0.6\n"
        << "=========================================\n";

    if (!serial.open(
            "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0",
            230400))
    {
        std::cout << "\nERROR abriendo puerto.\n";
        return 1;
    }

    for (;;)
    {
        std::cout
            << "\n"
            << "1) RESET_SOFTCFG\n"
            << "2) PRODUCT_ID\n"
            << "3) VERSION\n"
            << "4) ESCUCHAR 5 SEGUNDOS\n"
            << "5) ENVIAR TRAMA HEX\n"
            << "0) SALIR\n\n"
            << "Opcion: ";

        int option = 0;

        std::cin >> option;

        switch (option)
        {
            case 1:
                sendCommand(
                    serial,
                    "RESET_SOFTCFG",
                    AMBE3000Protocol::buildResetSoftCfg());
                break;

            case 2:
                sendCommand(
                    serial,
                    "PRODUCT_ID",
                    AMBE3000Protocol::buildProductId());
                break;

            case 3:
                sendCommand(
                    serial,
                    "VERSION",
                    AMBE3000Protocol::buildVersion());
                break;

            case 4:
            {
                std::cout << "\nEscuchando...\n";

                auto start =
                    std::chrono::steady_clock::now();

                while (true)
                {
                    auto now =
                        std::chrono::steady_clock::now();

                    if (std::chrono::duration_cast<
                            std::chrono::seconds>(
                            now - start).count() >= 5)
                    {
                        break;
                    }

                    std::vector<uint8_t> rx;

                    if (serial.readFrame(
                            rx,
                            250,
                            20))
                    {
                        showFrame(rx);
                    }
                }

                break;
            }

            case 5:
            {
                std::cin.ignore();

                std::cout
                    << "\nIntroduzca la trama HEX:\n\n";

                std::string line;

                std::getline(
                    std::cin,
                    line);

                auto tx =
                    parseHexString(line);

                std::cout
                    << "\nTX (" << tx.size()
                    << " bytes)";

                dumpHex(tx);

                if (!serial.write(tx))
                {
                    std::cout
                        << "\nERROR enviando trama.\n";

                    break;
                }

                std::vector<uint8_t> rx;

                if (!serial.readFrame(
                        rx,
                        2000,
                        20))
                {
                    std::cout
                        << "\nTimeout esperando respuesta.\n";

                    break;
                }

                showFrame(rx);

                break;
            }

            case 0:
                return 0;

            default:
                std::cout
                    << "\nOpcion no valida.\n";
        }
    }
}