#include "device/AMBE3000Device.h"


#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

#include "Logger.h"
#include "protocol/AMBE3000Protocol.h"
#include "protocol/DV3KResponse.h"
#include "protocol/AMBEFrame.h"


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

bool AMBE3000Device::sendDV3KCommand(
    const std::vector<uint8_t>& command,
    DV3KResponse& response)
{
    std::vector<uint8_t> rx;

    if (!m_serial.write(command))
        return false;

    std::this_thread::sleep_for(
        std::chrono::milliseconds(20));

    if (!m_serial.readFrame(rx, 2000, 20))
        return false;

    AMBEFrame frame;

    if (!frame.deserialize(rx))
        return false;

    std::vector<uint8_t> dv3k;

    dv3k.push_back(
        static_cast<uint8_t>(frame.command >> 8));

    dv3k.push_back(
        static_cast<uint8_t>(frame.command & 0xFF));

    dv3k.insert(
        dv3k.end(),
        frame.payload.begin(),
        frame.payload.end());

    return response.parse(dv3k);
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

   /* Logger::info("Enviando 35 ZERO_PACKET...");

    for (int i = 0; i < 35; i++)
    {
        m_serial.write(zero);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(1));
    }

    Logger::info("ZERO_PACKET enviados.");

    std::this_thread::sleep_for(
       std::chrono::milliseconds(5)); */

    Logger::info("Consultando PRODUCT_ID...");

DV3KResponse response;

if (!sendDV3KCommand(
        AMBE3000Protocol::buildProductId(),
        response))
{
    Logger::error("No se pudo obtener el PRODUCT_ID.");
    return false;
}

m_product = response.productId();

Logger::info(
    "Producto detectado: " +
    m_product);
    
    Logger::info("Consultando VERSION...");

if (!sendDV3KCommand(
        AMBE3000Protocol::buildVersion(),
        response))
{
    Logger::error("No se pudo obtener VERSION.");
    return false;
}

m_firmware = response.version();

Logger::info(
    "Firmware detectado: " +
    m_firmware);
    
    Logger::info("Enviando RESET_SOFTCFG...");

if (!sendDV3KCommand(
        AMBE3000Protocol::buildResetSoftCfg(),
        response))
{
    Logger::error("No se pudo completar RESET.");
    return false;
}

if (!response.isReady())
{
    Logger::error("El codec no respondió READY.");
    return false;
}

Logger::info("Codec inicializado correctamente.");
    
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
    if (!m_product.empty())
        return m_product;

    return "DVMEGA AMBE3000";
}

std::string AMBE3000Device::getFirmware() const
{
    if (!m_firmware.empty())
        return m_firmware;

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