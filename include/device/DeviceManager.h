#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <memory>
#include <vector>

#include "device/IDevice.h"

class DeviceManager
{
public:

    DeviceManager();

    bool initialize();

    void shutdown();

    void addDevice(
        std::shared_ptr<IDevice> device);

    bool removeDevice(
        std::shared_ptr<IDevice> device);

    std::shared_ptr<IDevice> findFreeDevice();

    bool reserve(
        std::shared_ptr<IDevice> device);

    void release(
        std::shared_ptr<IDevice> device);

    std::size_t count() const;

    const std::vector<std::shared_ptr<IDevice>>& devices() const;

private:

    std::vector<std::shared_ptr<IDevice>> m_devices;
};

#endif