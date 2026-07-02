#include "codec/CodecJob.h"

CodecJob::CodecJob()
{
    type = CodecJobType::Encode;

    state = CodecJobState::Pending;

    created = std::chrono::steady_clock::now();

    started = created;

    finished = created;
}