#include "protocol/AMBEFrame.h"

#include <iomanip>
#include <sstream>

AMBEFrame::AMBEFrame()
{
    clear();
}

void AMBEFrame::clear()
{
    start = 0x61;
    length = 0;
    command = 0;
    payload.clear();
}

bool AMBEFrame::deserialize(
    const std::vector<uint8_t>& data)
{
    clear();

    if (data.size() < 5)
        return false;

    if (data[0] != 0x61)
        return false;

    start = data[0];

    length =
        (static_cast<uint16_t>(data[1]) << 8) |
        static_cast<uint16_t>(data[2]);

    command =
        (static_cast<uint16_t>(data[3]) << 8) |
        static_cast<uint16_t>(data[4]);

    payload.assign(
        data.begin() + 5,
        data.end());

    return true;
}

std::vector<uint8_t>
AMBEFrame::serialize() const
{
    std::vector<uint8_t> frame;

    frame.push_back(start);

    frame.push_back(
        static_cast<uint8_t>(length >> 8));

    frame.push_back(
        static_cast<uint8_t>(length & 0xFF));

    frame.push_back(
        static_cast<uint8_t>(command >> 8));

    frame.push_back(
        static_cast<uint8_t>(command & 0xFF));

    frame.insert(
        frame.end(),
        payload.begin(),
        payload.end());

    return frame;
}

std::string
AMBEFrame::toString() const
{
    std::stringstream ss;

    ss << std::uppercase << std::hex;

    ss << "START   : 0x"
       << std::setw(2)
       << std::setfill('0')
       << static_cast<int>(start)
       << '\n';

    ss << "LENGTH  : "
       << std::dec
       << length
       << '\n';

    ss << std::uppercase << std::hex;

    ss << "COMMAND : 0x"
       << std::setw(4)
       << std::setfill('0')
       << command
       << '\n';

    ss << "PAYLOAD : ";

    if (payload.empty())
    {
        ss << "(vacío)";
    }
    else
    {
        for (std::size_t i = 0; i < payload.size(); ++i)
        {
            ss << std::setw(2)
               << std::setfill('0')
               << static_cast<int>(payload[i]);

            if (i + 1 != payload.size())
                ss << ' ';
        }
    }

    ss << '\n';

    return ss.str();
}

void
AMBEFrame::appendByte(
    uint8_t value)
{
    payload.push_back(value);

    length =
        static_cast<uint16_t>(
            payload.size() + 1);
}

void
AMBEFrame::appendData(
    const std::vector<uint8_t>& data)
{
    payload.insert(
        payload.end(),
        data.begin(),
        data.end());

    length =
        static_cast<uint16_t>(
            payload.size() + 1);
}

void
AMBEFrame::setPayload(
    const std::vector<uint8_t>& data)
{
    payload = data;

    length =
        static_cast<uint16_t>(
            payload.size() + 1);
}