#pragma once

#include <stdint.h>
#include <stddef.h>

#include "efiMemory.h"
#include "Bitmap.h"
#include "memory.h"

class PageFrameAllocator
{
public:
    Bitmap PageBitmap;

    void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR *mMap, size_t mMapSize, size_t mMapDescSize);
    void FreePage(void *address);
    void FreePages(void *address, uint64_t pageCount);
    void LockPage(void *address);
    void LockPages(void *address, uint64_t pageCount);
    void *RequestPage();
    uint64_t GetFreeRAM();
    uint64_t GetUsedRAM();
    uint64_t GetReservedRAM();

private:
    void InitBitmap(size_t bitmapSize, void *bufferAddress);
    void UnreservePage(void *address);
    void UnreservePages(void *address, uint64_t pageCount);
    void ReservePage(void *address);
    void ReservePages(void *address, uint64_t pageCount);
};