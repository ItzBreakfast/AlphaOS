#include <stdint.h>

#include "PageTableManager.h"
#include "PageMapIndexer.h"
#include "PageFrameAllocator.h"

PageTableManager::PageTableManager(PageTable *PML4Address)
{
    this->PML4 = PML4Address;
}

void PageTableManager::MapMemory(void *virtualMemory, void *physicalMemory) 
{
    PageMapIndexer indexer = PageMapIndexer((uint64_t)virtualMemory);
    PageDirectoryEntry PDE;

    PDE = PML4->entries[indexer.PDP_i];

    PageTable *PDP;

    if (!PDE.Present) 
    {
        PDP = (PageTable *)GlobalAllocator.RequestTable();
    }
}