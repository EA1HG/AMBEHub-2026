#ifndef SESSION_H
#define SESSION_H

#include <chrono>
#include <string>

enum class SessionState
{
    CONNECTING,
    CONNECTED,
    AUTHENTICATED
};

class Session
{
public:

    Session();

    int id;

    std::string ip;

    int port;

    std::string username;

    std::string clientName;

    std::string clientVersion;

    bool authenticated;

    SessionState state;

    std::chrono::steady_clock::time_point connectedTime;

    std::chrono::steady_clock::time_point lastPing;
};

#endif