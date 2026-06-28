#ifndef AMBEFRAME_H
#define AMBEFRAME_H

#include <cstdint>
#include <string>
#include <vector>

class AMBEFrame
{
public:

    AMBEFrame();

    void clear();

    bool deserialize(
        const std::vector<uint8_t>& data);

    std::vector<uint8_t> serialize() const;

    std::string toString() const;

public:

    uint8_t start;

    uint16_t length;

    uint16_t command;

    std::vector<uint8_t> payload;
};

#endif