#include "device/DeviceManager.h"

#include <algorithm>

#include "Logger.h"
#include "device/DummyDevice.h"
#include "device/AMBE3000Device.h"

DeviceManager::DeviceManager()
{
}

bool DeviceManager::initialize()
{
    Logger::info("Inicializando DeviceManager...");

    //
    // Intentamos abrir primero un DVMEGA.
    //

    auto ambe =
        std::make_shared<AMBE3000Device>();

    if (ambe->open())
    {
        addDevice(ambe);

        Logger::info(
            "DVMEGA inicializado correctamente.");
    }
    else
    {
        Logger::warning(
            "No se encontró un DVMEGA. Usando DummyDevice.");

        auto dummy =
            std::make_shared<DummyDevice>();

        dummy->open();

        addDevice(dummy);
    }

    Logger::info(
        "Dispositivos registrados: "
        + std::to_string(count()));

    return true;
}

void DeviceManager::shutdown()
{
    Logger::info("Cerrando DeviceManager...");

    for (auto& device : m_devices)
        device->close();

    m_devices.clear();
}

void DeviceManager::addDevice(
    std::shared_ptr<IDevice> device)
{
    m_devices.push_back(device);

    Logger::info(
        "Registrado: "
        + device->getName());
}

bool DeviceManager::removeDevice(
    std::shared_ptr<IDevice> device)
{
    auto it =
        std::find(
            m_devices.begin(),
            m_devices.end(),
            device);

    if (it == m_devices.end())
        return false;

    (*it)->close();

    m_devices.erase(it);

    return true;
}

std::shared_ptr<IDevice>
DeviceManager::findFreeDevice()
{
    for (auto& device : m_devices)
    {
        if (device->getState() ==
            DeviceState::FREE)
        {
            return device;
        }
    }

    return nullptr;
}

bool DeviceManager::reserve(
    std::shared_ptr<IDevice> device)
{
    if (!device)
        return false;

    if (device->getState() !=
        DeviceState::FREE)
        return false;

    device->setState(
        DeviceState::BUSY);

    return true;
}

void DeviceManager::release(
    std::shared_ptr<IDevice> device)
{
    if (!device)
        return;

    device->setState(
        DeviceState::FREE);
}

std::size_t DeviceManager::count() const
{
    return m_devices.size();
}

const std::vector<std::shared_ptr<IDevice>>&
DeviceManager::devices() const
{
    return m_devices;
}