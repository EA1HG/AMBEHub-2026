#include "protocol/PCMFrame.h"

PCMFrame::PCMFrame()
{
    clear();
}

void PCMFrame::clear()
{
    m_samples.fill(0);
}

int16_t& PCMFrame::operator[](std::size_t index)
{
    return m_samples[index];
}

const int16_t& PCMFrame::operator[](std::size_t index) const
{
    return m_samples[index];
}

std::array<int16_t, PCMFrame::SAMPLE_COUNT>&
PCMFrame::samples()
{
    return m_samples;
}

const std::array<int16_t, PCMFrame::SAMPLE_COUNT>&
PCMFrame::samples() const
{
    return m_samples;
}

std::vector<uint8_t>
PCMFrame::toBytes() const
{
    std::vector<uint8_t> bytes;

    bytes.reserve(SAMPLE_COUNT * 2);

    for (int16_t sample : m_samples)
    {
        //
        // Little Endian
        //

        bytes.push_back(
            static_cast<uint8_t>(
                sample & 0xFF));

        bytes.push_back(
            static_cast<uint8_t>(
                (sample >> 8) & 0xFF));
    }

    return bytes;
}

bool
PCMFrame::fromBytes(
    const std::vector<uint8_t>& bytes)
{
    if (bytes.size() != SAMPLE_COUNT * 2)
        return false;

    for (std::size_t i = 0; i < SAMPLE_COUNT; i++)
    {
        uint16_t value =
            static_cast<uint16_t>(bytes[i * 2]) |
            (static_cast<uint16_t>(bytes[i * 2 + 1]) << 8);

        m_samples[i] =
            static_cast<int16_t>(value);
    }

    return true;
}