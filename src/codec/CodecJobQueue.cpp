#include "codec/CodecJobQueue.h"

CodecJobQueue::CodecJobQueue()
{
}

void CodecJobQueue::push(
    const CodecJob& job)
{
    m_queue.push(job);
}

CodecJob CodecJobQueue::pop()
{
    CodecJob job = m_queue.front();

    m_queue.pop();

    return job;
}

bool CodecJobQueue::empty() const
{
    return m_queue.empty();
}

std::size_t CodecJobQueue::size() const
{
    return m_queue.size();
}

void CodecJobQueue::clear()
{
    while (!m_queue.empty())
        m_queue.pop();
}