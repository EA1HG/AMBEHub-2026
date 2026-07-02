#ifndef PCMFRAME_H
#define PCMFRAME_H

#include <array>
#include <cstdint>
#include <vector>


class PCMFrame
{
public:

    static constexpr std::size_t SAMPLE_COUNT = 160;

    PCMFrame();

    void clear();

    int16_t& operator[](std::size_t index);

    const int16_t& operator[](std::size_t index) const;

    std::array<int16_t, SAMPLE_COUNT>& samples();

    const std::array<int16_t, SAMPLE_COUNT>& samples() const;
    
   std::vector<uint8_t> toBytes() const;

bool fromBytes(
    const std::vector<uint8_t>& bytes); 

private:

    std::array<int16_t, SAMPLE_COUNT> m_samples;
};

#endif