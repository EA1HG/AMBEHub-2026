#ifndef IDEVICE_H
#define IDEVICE_H

#include <string>

enum class DeviceState
{
    OFFLINE,
    FREE,
    RESERVED,
    BUSY
};

enum class DeviceType
{
    UNKNOWN,
    THUMBDV,
    AMBE3000,
    DV3000USB,
    OPENGD77,
    MD380
};

class IDevice
{
public:

    virtual ~IDevice() = default;

    virtual bool open() = 0;

    virtual void close() = 0;

    virtual bool reset() = 0;

    virtual std::string getName() const = 0;

    virtual std::string getFirmware() const = 0;

    virtual DeviceType getType() const = 0;

    virtual DeviceState getState() const = 0;

    virtual void setState(
        DeviceState state) = 0;
};

#endif