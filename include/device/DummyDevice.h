#ifndef DUMMYDEVICE_H
#define DUMMYDEVICE_H

#include "device/IDevice.h"

class DummyDevice : public IDevice
{
public:

    DummyDevice();

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

    DeviceState m_state;
};

#endif