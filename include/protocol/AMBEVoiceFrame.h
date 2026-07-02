#ifndef AMBEVOICEFRAME_H
#define AMBEVOICEFRAME_H

#include <array>
#include <cstdint>
#include <vector>

class AMBEVoiceFrame
{
public:

    static constexpr std::size_t FRAME_SIZE = 9;

    AMBEVoiceFrame();

    void clear();

    uint8_t& operator[](std::size_t index);

    const uint8_t& operator[](std::size_t index) const;

    std::array<uint8_t, FRAME_SIZE>& data();

    const std::array<uint8_t, FRAME_SIZE>& data() const;

    std::vector<uint8_t> toBytes() const;

    bool fromBytes(
        const std::vector<uint8_t>& bytes);

private:

    std::array<uint8_t, FRAME_SIZE> m_data;
};

#endif