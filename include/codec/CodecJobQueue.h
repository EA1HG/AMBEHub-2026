#ifndef CODECJOBQUEUE_H
#define CODECJOBQUEUE_H

#include <queue>

#include "codec/CodecJob.h"

class CodecJobQueue
{
public:

    CodecJobQueue();

    void push(
        const CodecJob& job);

    CodecJob pop();

    bool empty() const;

    std::size_t size() const;

    void clear();

private:

    std::queue<CodecJob> m_queue;
};

#endif