#ifndef DV3KCOMMANDS_H
#define DV3KCOMMANDS_H

#include <cstdint>

namespace DV3KCommands
{
    // Control
    constexpr uint16_t PRODUCT_ID     = 0x0030;
    constexpr uint16_t VERSION        = 0x0031;
    constexpr uint16_t RESET_SOFTCFG  = 0x0034;
    constexpr uint16_t READY          = 0x0039;

    // Audio
    constexpr uint16_t AMBE           = 0x0001;
    constexpr uint16_t PCM            = 0x0002;
}

#endif