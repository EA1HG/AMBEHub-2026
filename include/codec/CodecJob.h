#ifndef CODECJOB_H
#define CODECJOB_H

#include <chrono>

#include "protocol/PCMFrame.h"
#include "protocol/AMBEVoiceFrame.h"

enum class CodecJobType
{
    Encode,
    Decode
};

enum class CodecJobState
{
    Pending,
    Running,
    Finished,
    Error
};

class CodecJob
{
public:

    CodecJob();

    CodecJobType type;

    CodecJobState state;

    PCMFrame pcm;

    AMBEVoiceFrame ambe;

    std::chrono::steady_clock::time_point created;

    std::chrono::steady_clock::time_point started;

    std::chrono::steady_clock::time_point finished;
};

#endif