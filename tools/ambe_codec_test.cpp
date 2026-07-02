#include <iomanip>
#include <iostream>

#include "audio/PCMGenerator.h"
#include "codec/CodecEngine.h"
#include "device/AMBE3000Device.h"
#include "protocol/AMBEVoiceFrame.h"
#include "protocol/PCMFrame.h"

static void dumpAMBE(const AMBEVoiceFrame& frame)
{
    const auto& data = frame.data();

    std::cout << "\nAMBE (" << data.size() << " bytes)\n\n";

    for (std::size_t i = 0; i < data.size(); i++)
    {
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
        << "        AMBE CODEC TEST\n"
        << "=========================================\n";

    AMBE3000Device device;

    if (!device.open())
    {
        std::cout << "\nERROR abriendo DVMEGA\n";
        return 1;
    }

    PCMFrame pcm;
    PCMGenerator::generateSilence(pcm);

    CodecEngine codec;

    AMBEVoiceFrame ambe;

    if (!codec.encode(device, pcm, ambe))
    {
        std::cout << "\nERROR codificando PCM\n";
        return 1;
    }

    dumpAMBE(ambe);

    device.close();

    return 0;
}