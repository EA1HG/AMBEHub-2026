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
            << " ";
    }

    std::cout << std::dec << std::endl;
}

int main()
{
    SerialPort serial;

    std::cout << "\n=========================================\n";
    std::cout << "        AMBEHub Diagnostic 0.3\n";
    std::cout << "=========================================\n\n";

    if (!serial.open(
            "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0",
            230400))
    {
        std::cout << "ERROR abriendo puerto.\n";
        return 1;
    }

    std::cout << "Puerto abierto correctamente.\n";

    auto tx =
        AMBE3000Protocol::buildResetSoftCfg();

    std::cout << "\nTX (" << tx.size() << " bytes)";
    dumpHex(tx);

    if (!serial.write(tx))
    {
        std::cout << "\nERROR escribiendo.\n";
        return 1;
    }

    std::cout << "\nEsperando respuestas durante 5 segundos...\n";

    auto start =
        std::chrono::steady_clock::now();

    int frameNumber = 0;
    int totalBytes = 0;

    while (true)
    {
        auto now =
            std::chrono::steady_clock::now();

        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now - start).count();

        if (elapsed >= 5000)
            break;

        std::vector<uint8_t> rx;

        if (!serial.readFrame(rx, 250, 20))
            continue;

        ++frameNumber;
        totalBytes += rx.size();

        std::cout << "\n----------------------------------------\n";
        std::cout << "FRAME #" << frameNumber << "\n";
        std::cout << "Bytes : " << rx.size() << "\n";

        dumpHex(rx);

        AMBEFrame frame;

        if (frame.deserialize(rx))
        {
            std::cout << "\n"
                      << frame.toString()
                      << std::endl;
        }
        else
        {
            std::cout << "\nNo se pudo interpretar la trama.\n";
        }
    }

    std::cout << "\n=========================================\n";
    std::cout << "Captura finalizada\n";
    std::cout << "Frames recibidos : " << frameNumber << "\n";
    std::cout << "Bytes recibidos  : " << totalBytes << "\n";
    std::cout << "=========================================\n";

    return 0;
}