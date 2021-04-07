#pragma once

#include <stdint.h>

#include "paging.h"
#include "PageMapIndexer.h"
#include "PageFrameAllocator.h"
#include "../memory.h"

class PageTableManager
{
public:
    PageTable *PML4;

    PageTableManager(PageTable *PML4Address);

    void MapMemory(void *virtualMemory, void *physicalMemory);
};

extern PageTableManager g_PageTableManager;