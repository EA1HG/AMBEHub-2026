#include <iomanip>
#include <iostream>

#include "audio/PCMGenerator.h"
#include "device/SerialPort.h"
#include "protocol/PCMFrame.h"

static void dumpHex(const std::vector<uint8_t>& data)
{
    for (std::size_t i = 0; i < data.size(); ++i)
    {
        if ((i % 16) == 0)
            std::cout << "\n";

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

int main()
{
    std::cout
        << "\n=========================================\n"
        << "         AMBE PCM TEST 0.2\n"
        << "=========================================\n";

    SerialPort serial;

    if (!serial.open(
            "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0",
            230400))
    {
        std::cout << "\nERROR abriendo puerto serie.\n";
        return 1;
    }

    std::cout << "\nPuerto serie abierto correctamente.\n";

    //
    // Generar un bloque PCM de silencio
    //

    PCMFrame pcm;

    PCMGenerator::generateSilence(pcm);

    auto bytes = pcm.toBytes();

    std::cout
        << "\nPCM generado correctamente.\n";

    std::cout
        << "\nNumero de muestras : "
        << PCMFrame::SAMPLE_COUNT
        << "\n";

    std::cout
        << "Numero de bytes    : "
        << bytes.size()
        << "\n";

    std::cout
        << "\nContenido:";

    dumpHex(bytes);

    return 0;
}