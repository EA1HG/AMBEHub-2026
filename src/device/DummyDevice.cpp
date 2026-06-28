#include "device/DummyDevice.h"

DummyDevice::DummyDevice()
{
    m_state = DeviceState::FREE;
}

bool DummyDevice::open()
{
    return true;
}

void DummyDevice::close()
{
}

bool DummyDevice::reset()
{
    return true;
}

std::string DummyDevice::getName() const
{
    return "Dummy Device";
}

std::string DummyDevice::getFirmware() const
{
    return "1.0";
}

DeviceType DummyDevice::getType() const
{
    return DeviceType::UNKNOWN;
}

DeviceState DummyDevice::getState() const
{
    return m_state;
}

void DummyDevice::setState(
    DeviceState state)
{
    m_state = state;
}