#pragma once

#include <stdint.h>

namespace PIT
{
    const uint64_t BaseFrequency = 1193182;

    extern double TimeSinceBoot;

    void Tick();
    void Sleepd(double seconds);
    void Sleep(uint64_t milliseconds);
    void SetDivisor(uint16_t divisor);
    void SetFrequency(uint64_t frequency);
    uint64_t GetFrequency();
}