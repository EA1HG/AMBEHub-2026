#include "device/DummyDevice.h"

#include "protocol/AMBEFrame.h"

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

bool DummyDevice::sendFrame(
    const AMBEFrame&)
{
    return false;
}

bool DummyDevice::exchangeFrame(
    const AMBEFrame&,
    AMBEFrame&)
{
    return false;
}

bool DummyDevice::sendRaw(
    const std::vector<uint8_t>&)
{
    return false;
}

bool DummyDevice::exchangeRaw(
    const std::vector<uint8_t>&,
    std::vector<uint8_t>&)
{
    return false;
}