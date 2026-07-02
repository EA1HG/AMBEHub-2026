#ifndef AMBE3000DEVICE_H
#define AMBE3000DEVICE_H

#include <string>
#include <vector>

#include "protocol/AMBEFrame.h"
#include "protocol/DV3KResponse.h"

#include "device/IDevice.h"
#include "device/SerialPort.h"

class AMBE3000Device : public IDevice
{
public:

    AMBE3000Device();

    bool open() override;

    void close() override;

    bool reset() override;

    std::string getName() const override;

    std::string getFirmware() const override;

    DeviceType getType() const override;

    DeviceState getState() const override;

    void setState(
        DeviceState state) override;

    bool sendFrame(
        const AMBEFrame& frame);

    bool exchangeFrame(
        const AMBEFrame& tx,
        AMBEFrame& rx);

    //
    // NUEVO
    // Intercambio RAW para los paquetes de AUDIO
    //

    bool exchangeRaw(
        const std::vector<uint8_t>& tx,
        std::vector<uint8_t>& rx);
        
    bool sendRaw(
    const std::vector<uint8_t>& tx);    

private:

    bool sendDV3KCommand(
        const std::vector<uint8_t>& command,
        DV3KResponse& response);

    bool initializeCodec();

    bool queryProduct();

    bool queryVersion();

    bool resetCodec();

    SerialPort m_serial;

    DeviceState m_state;

    //
    // Información del codec
    //

    std::string m_product;

    std::string m_firmware;
};

#endif