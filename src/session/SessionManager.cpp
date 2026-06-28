#include "session/SessionManager.h"

SessionManager::SessionManager()
{
}

Session* SessionManager::find(
    const std::string& ip,
    int port)
{
    for (auto& session : m_sessions)
    {
        if (session.ip == ip &&
            session.port == port)
        {
            return &session;
        }
    }

    return nullptr;
}

Session& SessionManager::create(
    const std::string& ip,
    int port)
{
    Session session;

    session.id = static_cast<int>(m_sessions.size()) + 1;

    session.ip = ip;

    session.port = port;

    session.state = SessionState::CONNECTED;

    m_sessions.push_back(session);

    return m_sessions.back();
}

std::vector<Session>& SessionManager::sessions()
{
    return m_sessions;
}