#include "protocol/AMBEVoiceFrame.h"

#include <algorithm>
#include <vector>

AMBEVoiceFrame::AMBEVoiceFrame()
{
    clear();
}

void AMBEVoiceFrame::clear()
{
    m_data.fill(0);
}

uint8_t& AMBEVoiceFrame::operator[](std::size_t index)
{
    return m_data[index];
}

const uint8_t& AMBEVoiceFrame::operator[](std::size_t index) const
{
    return m_data[index];
}

std::array<uint8_t, AMBEVoiceFrame::FRAME_SIZE>&
AMBEVoiceFrame::data()
{
    return m_data;
}

const std::array<uint8_t, AMBEVoiceFrame::FRAME_SIZE>&
AMBEVoiceFrame::data() const
{
    return m_data;
}

std::vector<uint8_t>
AMBEVoiceFrame::toBytes() const
{
    return std::vector<uint8_t>(
        m_data.begin(),
        m_data.end());
}

bool
AMBEVoiceFrame::fromBytes(
    const std::vector<uint8_t>& bytes)
{
    if (bytes.size() != FRAME_SIZE)
        return false;

    std::copy(
        bytes.begin(),
        bytes.end(),
        m_data.begin());

    return true;
}