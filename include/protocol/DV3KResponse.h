#ifndef DV3KRESPONSE_H
#define DV3KRESPONSE_H

#include <cstdint>
#include <string>
#include <vector>

class DV3KResponse
{
public:

    DV3KResponse();

    void clear();

    bool parse(
        const std::vector<uint8_t>& data);

    bool isReady() const;

    bool isProductId() const;

    bool isVersion() const;

    uint16_t command() const;

    std::string productId() const;

    std::string version() const;

    std::string commandName() const;

private:

    uint16_t m_command;

    std::vector<uint8_t> m_payload;
};

#endif