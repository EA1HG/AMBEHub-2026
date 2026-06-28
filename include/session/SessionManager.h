#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <vector>

#include "session/Session.h"

class SessionManager
{
public:

    SessionManager();

    Session* find(
        const std::string& ip,
        int port);

    Session& create(
        const std::string& ip,
        int port);

    std::vector<Session>& sessions();

private:

    std::vector<Session> m_sessions;
};

#endif