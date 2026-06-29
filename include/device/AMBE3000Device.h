#ifndef AMBE3000DEVICE_H
#define AMBE3000DEVICE_H

#include <string>

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

private:

    SerialPort m_serial;

    DeviceState m_state;

    //
    // Información del codec
    //

    std::string m_product;

    std::string m_firmware;
};

#endif