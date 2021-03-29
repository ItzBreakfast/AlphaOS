#pragma once

#include <stdint.h>

enum PT_Flag
{
    Present = 0,
    ReadWrite = 1,
    UserSuper = 2,
    WriteThrough = 3,
    CacheDisabled = 4,
    Accessed = 5,
    LargerPages = 7,
    Custom0 = 9,
    Custom1 = 10,
    Custom2 = 11,
    NX = 63 // only if supported
};

/*
    bool Present : 1;
    bool ReadWrite : 1;
    bool UserSuper : 1;
    bool WriteThrough : 1;
    bool CacheDisabled : 1;
    bool Accessed : 1;
    bool ignore0 : 1;
    bool LargerPages : 1;
    bool ignore1 : 1;
    uint8_t Available : 3;
    uint64_t Address : 52;
*/

struct PageDirectoryEntry
{
    uint64_t Value;

    void SetFlag(PT_Flag flag, bool enabled);
    void SetAddress(uint64_t address);
    bool GetFlag(PT_Flag flag);
    uint64_t GetAddress();
};

struct PageTable
{
    PageDirectoryEntry entries[512];
} __attribute__((aligned(0x1000)));