#ifndef IDEVICE_H
#define IDEVICE_H

#include <string>
#include "protocol/AMBEFrame.h"
#include <vector>
#include <cstdint>

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

//
// Comunicación DV3K
//

virtual bool sendFrame(
    const AMBEFrame& frame) = 0;

virtual bool exchangeFrame(
    const AMBEFrame& tx,
    AMBEFrame& rx) = 0;
    
//
// Comunicación AUDIO DV3K (RAW)
//

virtual bool sendRaw(
    const std::vector<uint8_t>& tx) = 0;

virtual bool exchangeRaw(
    const std::vector<uint8_t>& tx,
    std::vector<uint8_t>& rx) = 0;    
};

#endif