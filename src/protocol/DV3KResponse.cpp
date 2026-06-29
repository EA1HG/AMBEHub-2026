#include "protocol/DV3KResponse.h"

DV3KResponse::DV3KResponse()
{
    clear();
}

void DV3KResponse::clear()
{
    m_command = 0;
    m_payload.clear();
}

bool DV3KResponse::parse(
    const std::vector<uint8_t>& data)
{
    clear();

    if (data.size() < 2)
        return false;

    m_command =
        (static_cast<uint16_t>(data[0]) << 8) |
        static_cast<uint16_t>(data[1]);

    if (data.size() > 2)
    {
        m_payload.assign(
            data.begin() + 2,
            data.end());

        //
        // Eliminamos NULL final
        //

        while (!m_payload.empty() &&
               m_payload.back() == 0x00)
        {
            m_payload.pop_back();
        }
    }

    return true;
}

bool DV3KResponse::isReady() const
{
    return m_command == 0x0039;
}

bool DV3KResponse::isProductId() const
{
    return m_command == 0x0030;
}

bool DV3KResponse::isVersion() const
{
    return m_command == 0x0031;
}

uint16_t DV3KResponse::command() const
{
    return m_command;
}

std::string DV3KResponse::productId() const
{
    return std::string(
        m_payload.begin(),
        m_payload.end());
}

std::string DV3KResponse::version() const
{
    return std::string(
        m_payload.begin(),
        m_payload.end());
}

std::string DV3KResponse::commandName() const
{
    switch (m_command)
    {
        case 0x0030:
            return "PRODUCT_ID";

        case 0x0031:
            return "VERSION";

        case 0x0039:
            return "READY";

        default:
            return "UNKNOWN";
    }
}