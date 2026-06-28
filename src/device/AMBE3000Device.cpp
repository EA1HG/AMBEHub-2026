#include "device/AMBE3000Device.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

#include "Logger.h"
#include "protocol/AMBE3000Protocol.h"

AMBE3000Device::AMBE3000Device()
{
    m_state = DeviceState::OFFLINE;
}

static std::string dumpHex(const std::vector<uint8_t>& data)
{
    std::stringstream ss;

    ss << std::uppercase << std::hex;

    for (std::size_t i = 0; i < data.size(); ++i)
    {
        ss << std::setw(2)
           << std::setfill('0')
           << static_cast<int>(data[i]);

        if (i + 1 != data.size())
            ss << ' ';
    }

    return ss.str();
}

bool AMBE3000Device::open()
{
    if (!m_serial.open(
            "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0",
            230400))
    {
        Logger::error("No se pudo abrir el DVMEGA.");
        return false;
    }

    Logger::info("DVMEGA abierto correctamente.");
    Logger::info("Inicializando codec AMBE3000...");

    //
    // Igual que hace AMBEserver:
    // enviar varios ZERO_PACKET antes del RESET.
    //

    auto zero =
        AMBE3000Protocol::buildZeroPacket();

    Logger::info("Enviando 35 ZERO_PACKET...");

    for (int i = 0; i < 35; i++)
    {
        m_serial.write(zero);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1));
    }

    Logger::info("ZERO_PACKET enviados.");

    std::this_thread::sleep_for(
        std::chrono::milliseconds(5));

    auto reset =
        AMBE3000Protocol::buildResetSoftCfg();

    Logger::info("Enviando RESET_SOFTCFG...");

    if (!m_serial.write(reset))
    {
        Logger::error("No se pudo enviar RESET.");

        return false;
    }

    std::vector<uint8_t> rx;

    Logger::info("Esperando respuesta...");

    if (m_serial.readFrame(
            rx,
            2000,
            20))
    {
        Logger::info(
            "Respuesta (" +
            std::to_string(rx.size()) +
            " bytes):");

        Logger::info(
            dumpHex(rx));
    }
    else
    {
        Logger::warning(
            "No se recibió respuesta al RESET.");
    }

    m_state = DeviceState::FREE;

    return true;
}

void AMBE3000Device::close()
{
    m_serial.close();

    m_state = DeviceState::OFFLINE;
}

bool AMBE3000Device::reset()
{
    Logger::info("Reset pendiente de implementar.");

    return true;
}

std::string AMBE3000Device::getName() const
{
    return "DVMEGA AMBE3000";
}

std::string AMBE3000Device::getFirmware() const
{
    return "Unknown";
}

DeviceType AMBE3000Device::getType() const
{
    return DeviceType::AMBE3000;
}

DeviceState AMBE3000Device::getState() const
{
    return m_state;
}

void AMBE3000Device::setState(
    DeviceState state)
{
    m_state = state;
}