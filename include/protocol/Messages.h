#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdint>

#pragma pack(push,1)

struct HelloMessage
{
    uint16_t protocolVersion;

    char clientName[32];

    char clientVersion[16];
};

struct LoginMessage
{
    char callsign[16];

    char password[32];
};

struct LoginReply
{
    uint8_t accepted;
};

#pragma pack(pop)

#endif