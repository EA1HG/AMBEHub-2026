#include "session/Session.h"

Session::Session()
{
    id = 0;

    ip = "";

    port = 0;

    username = "";

    clientName = "";

    clientVersion = "";

    authenticated = false;

    state = SessionState::CONNECTING;

    connectedTime = std::chrono::steady_clock::now();

    lastPing = connectedTime;
}